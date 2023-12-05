#define ENTRY_FILE
#include "app.h"
#include "apiset.h"
#include "Engine/src/core/Log.h"

#include <iostream>


namespace std
{
	pair<LONG, LONG> operator-(const pair<LONG, LONG>& lhs, const pair<LONG, LONG>& rhs)
	{
		return { lhs.first - rhs.first, lhs.second - rhs.second };
	}

	pair<LONG, LONG> operator+=(pair<LONG, LONG>& lhs, const pair<LONG, LONG>& rhs)
	{
		lhs.first += rhs.first;
		lhs.second += rhs.second;
		return lhs;
	}
}

#define toFloat(x) static_cast<float>(x)

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)


class ExampleLayer : public WLD::Layer
{
public:
	ExampleLayer()
		: Layer("Render"), m_CamSpeed(1.0f)
	{
		// multicolour squire data
		float multiColourVertices[] =
		{
			-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.0f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,
													   
			-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, -0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		};

		uint32_t multiColourIndices[] =
		{
			0, 1, 4,
			1, 2, 4,
			2, 3, 4,
			3, 0, 4,

			2, 1, 7,
			1, 5, 7,
			5, 6, 7,
			6, 2, 7
		};

		std::string_view multiColourVertexSrc =
		R"(
			#version 460 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Colour;

			out vec4 v_Colour;
			uniform mat4 u_MVP;
			
			void main()
			{
				v_Colour = a_Colour;
				gl_Position = u_MVP * vec4(a_Position, 1.0);
			}
		)";

		std::string_view multiColourFragmentSrc =
		R"(
			#version 460 core
			
			layout(location = 0) out vec4 colour;

			in vec4 v_Colour;
			
			void main()
			{
				colour = v_Colour;
			}
		)";

		// background data
		float backgroundVertices[] =
		{
			-1.0f, -1.0f, 0.0f,
			-1.0f,  1.0f, 0.0f,
			 1.0f,  1.0f, 0.0f,
			 1.0f, -1.0f, 0.0f
		};

		uint32_t backgroundIndices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		std::string_view backgroundVertexSrc =
		R"(
			#version 460 core
			
			layout(location = 0) in vec3 a_Position;
			
			void main()
			{
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string_view backgroundFragmentSrc =
		R"(
			#version 460 core
			
			layout(location = 0) out vec4 colour;
			
			void main()
			{
				colour = vec4(1.0f, 105.0f / 255.0f, 180.0f / 255.0f, 1.0f);
			}
		)";

		// Vertex buffer and index buffer creation
		std::shared_ptr<WLD::Graphics::Renderer::Buffers::VertexBuffer> vertexBuffer;
		std::shared_ptr<WLD::Graphics::Renderer::Buffers::IndexBuffer> indexBuffer;

		// multicolour squire creation
		m_MultiColourShader.reset(WLD::Graphics::Renderer::Shader::Create(multiColourVertexSrc, multiColourFragmentSrc));
		m_MultiColourVertexArray.reset(WLD::Graphics::Renderer::VertexArray::Create());

		vertexBuffer.reset(WLD::Graphics::Renderer::Buffers::VertexBuffer::Create(multiColourVertices, sizeof(multiColourVertices)));
		indexBuffer.reset(WLD::Graphics::Renderer::Buffers::IndexBuffer::Create(multiColourIndices, sizeof(multiColourIndices) / sizeof(uint32_t)));

		vertexBuffer->SetLayout
		({
			{ WLD::Graphics::Renderer::Buffers::ShaderDataType::Float3, "a_Position" },
			{ WLD::Graphics::Renderer::Buffers::ShaderDataType::Float4, "a_Colour" }
		});

		m_MultiColourVertexArray->AddVertexBuffer(vertexBuffer);
		m_MultiColourVertexArray->SetIndexBuffer(indexBuffer);

		// background creation
		m_BackgroundShader.reset(WLD::Graphics::Renderer::Shader::Create(backgroundVertexSrc, backgroundFragmentSrc));
		m_BackgroundVA.reset(WLD::Graphics::Renderer::VertexArray::Create());

		vertexBuffer.reset(WLD::Graphics::Renderer::Buffers::VertexBuffer::Create(backgroundVertices, sizeof(backgroundVertices)));
		indexBuffer.reset(WLD::Graphics::Renderer::Buffers::IndexBuffer::Create(backgroundIndices, sizeof(backgroundIndices) / sizeof(uint32_t)));

		vertexBuffer->SetLayout
		({
			{ WLD::Graphics::Renderer::Buffers::ShaderDataType::Float3, "a_Position" }
		});

		m_BackgroundVA->AddVertexBuffer(vertexBuffer);
		m_BackgroundVA->SetIndexBuffer(indexBuffer);

		WLD::Window& window = WLD::Application::Get().GetWindow();
		m_Camera.reset(new WLD::Graphics::Camera::PerspectiveCamera(45.0f, toFloat(window.GetHeight()), toFloat(window.GetWidth()), 0.001f, 100.0f));
		m_Camera->setUp({ 0.0f, 1.0f, 0.0f });
	}

	void OnUpdate() override
	{
		WLD::Graphics::Renderer::RenderCommand::Clear();
		WLD::Graphics::Renderer::Renderer::BeginScene(m_Camera);
		WLD::Graphics::Renderer::Renderer::Submit(m_BackgroundVA, m_BackgroundShader);

		std::pair<double, double> rotation = getRotation();
		m_Camera->setFront({toFloat(rotation.first / 2.0), toFloat(rotation.second / 2.0), 0.0f});
		m_Camera->setPos(getMovement(m_CamSpeed));
		
		WLD::Graphics::Renderer::Renderer::Submit(m_MultiColourVertexArray, m_MultiColourShader);
		WLD::Graphics::Renderer::Renderer::EndScene();
	}

	void OnImGuiDraw() override
	{
		static glm::vec3 pos(0.0f);
		static glm::vec3 rot(0.0f);

		ImGui::Begin("3D Object");
		ImGui::Text("Rotation");
		ImGui::SliderFloat3("x, y, z", &rot.x, -360.0f, 360.0f);
		ImGui::Separator();
		ImGui::Text("Position");
		ImGui::SliderFloat3("x, y, z ", &pos.x, -10.0f, 10.0f);
		ImGui::End();

		ImGui::Begin("Camera");
		ImGui::Text("Speed");
		ImGui::SliderFloat("speed", &m_CamSpeed, 0.0f, 10.0f, "%.1f");
		ImGui::End();

		m_Camera->setPosition(pos);
		m_Camera->setRotation(rot);
	}

	void OnEvent(WLD::Event& e) override
	{
		WLD::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WLD::WindowResizeEvent>(BIND_EVENT_FN(ExampleLayer::OnWindowResize));
	}

private:
	glm::vec3 getMovement(float speed)
	{
		float x = 0.0f, y = 0.0f, z = 0.0f;

		float deltaTime = toFloat(WLD::Application::Get().GetDeltaTime());

		if (WLD::Input::IsKeyPressed(WLD_KEY_UP)        || WLD::Input::IsKeyPressed(WLD_KEY_W))	x += speed * deltaTime;
		if (WLD::Input::IsKeyPressed(WLD_KEY_DOWN)      || WLD::Input::IsKeyPressed(WLD_KEY_S))	x -= speed * deltaTime;
		if (WLD::Input::IsKeyPressed(WLD_KEY_PAGE_UP)   || WLD::Input::IsKeyPressed(WLD_KEY_R)) y += speed * deltaTime;
		if (WLD::Input::IsKeyPressed(WLD_KEY_PAGE_DOWN) || WLD::Input::IsKeyPressed(WLD_KEY_F))	y -= speed * deltaTime;
		if (WLD::Input::IsKeyPressed(WLD_KEY_RIGHT)     || WLD::Input::IsKeyPressed(WLD_KEY_D))	z += speed * deltaTime;
		if (WLD::Input::IsKeyPressed(WLD_KEY_LEFT)      || WLD::Input::IsKeyPressed(WLD_KEY_A))	z -= speed * deltaTime;

		return { x, y, z };
	}

	std::pair<LONG, LONG> getRotation()
	{
		std::pair<LONG, LONG> posNow = WLD::Input::GetMousePosition();
		static std::pair<LONG, LONG> lastPos = posNow;
		static std::pair<LONG, LONG> total = { 0, 0 };
		std::pair<LONG, LONG> delta = posNow - lastPos;

		if (WLD::Input::IsMousButtonPressed(WLD_MOUSE_BUTTON_RIGHT) ||
			WLD::Input::IsKeyPressed(WLD_KEY_LEFT_CONTROL) ||
			WLD::Input::IsKeyPressed(WLD_KEY_RIGHT_CONTROL))
			total += delta;

//		     if (total.first  < -360)  total.first  += 720;
//		else if (total.first  >  360)  total.first  -= 720;
//		     if (total.second < -360)  total.second += 720;
//		else if (total.second >  360)  total.second -= 720;

		lastPos = posNow;
		return total;
	}

	bool OnWindowResize(WLD::WindowResizeEvent& e)
	{
		m_Camera->setProjection(45.0f, toFloat(e.GetHeight()), toFloat(e.GetWidth()), 0.001f, 100.0f);
		return true;
	}

private:
	std::shared_ptr<WLD::Graphics::Renderer::Shader> m_MultiColourShader;
	std::shared_ptr<WLD::Graphics::Renderer::VertexArray> m_MultiColourVertexArray;

	std::shared_ptr<WLD::Graphics::Renderer::Shader> m_BackgroundShader;
	std::shared_ptr<WLD::Graphics::Renderer::VertexArray> m_BackgroundVA;
	std::shared_ptr<WLD::Graphics::Camera::PerspectiveCamera> m_Camera;

	float m_CamSpeed;
};

class SandBox : public WLD::Application
{
public:
	SandBox(bool* run)
		: Application(run)
	{
		std::cout << "sand box created" << std::endl;
		PushLayer(new ExampleLayer);
	}

	~SandBox()
	{
		std::cout << "sand box destroyed" << std::endl;
	}
};

WLD::Application* WLD::CreateApplication(bool* run, int argc, char** argv)
{
	if (argc > 1 && run[2] == false)
	{
		if (strcmp(argv[1], "-opengl"))
		{
			WLD::Graphics::Renderer::Renderer::SetAPI(WLD::Graphics::Renderer::RendererAPI::API::OpenGL);
			run[2] = true;
		}
		else if (strcmp(argv[1], "-dx12"))
		{
			WLD::Graphics::Renderer::Renderer::SetAPI(WLD::Graphics::Renderer::RendererAPI::API::DirectX12);
			run[2] = true;
		}
	}

	if (!run[2])
	{
		return new SetAPI(run);
	}

	return new SandBox(run);
}
