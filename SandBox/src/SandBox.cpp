#define ENTRY_FILE
#include "app.h"
#include "apiset.h"
#include "Engine/src/core/Log.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Engine/src/platform/OpenGL/Shader.h"

#include <iostream>

namespace std
{
	static pair<LONG, LONG> operator-(const pair<LONG, LONG>& lhs, const pair<LONG, LONG>& rhs)
	{
		return { lhs.first - rhs.first, lhs.second - rhs.second };
	}

	static pair<LONG, LONG> operator+=(pair<LONG, LONG>& lhs, const pair<LONG, LONG>& rhs)
	{
		lhs.first += rhs.first;
		lhs.second -= rhs.second;
		return lhs;
	}
}

#define toFloat(x) static_cast<float>(x)


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
			uniform mat4 u_Transform;
			
			void main()
			{
				v_Colour = a_Colour;
				gl_Position = u_MVP * u_Transform * vec4(a_Position, 1.0);
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
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f
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
			
			uniform vec3 u_Colour;

			void main()
			{
				colour = vec4(u_Colour, 1.0f);
			}
		)";

		// texture shader data
		std::string_view TexureVertexSrc =
		R"(
			#version 460 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			out vec2 v_TexCoord;
			
			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string_view TexureFragmentSrc =
		R"(
			#version 460 core
			
			layout(location = 0) out vec4 colour;
			
			in vec2 v_TexCoord;

			void main()
			{
				colour = vec4(v_TexCoord, 0.0, 1.0f);
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
			{ WLD::Graphics::Renderer::Buffers::ShaderDataType::Float3, "a_Position" },
			{ WLD::Graphics::Renderer::Buffers::ShaderDataType::Float2, "a_TexCoord" }
		});

		m_BackgroundVA->AddVertexBuffer(vertexBuffer);
		m_BackgroundVA->SetIndexBuffer(indexBuffer);

		// texture shader creation
		m_TextureShader.reset(WLD::Graphics::Renderer::Shader::Create(TexureVertexSrc, TexureFragmentSrc));

		// camera creation
		WLD::Window& window = WLD::Application::Get().GetWindow();
		m_Camera.reset(new WLD::Graphics::Camera::PerspectiveCamera(45.0f, toFloat(window.GetHeight()), toFloat(window.GetWidth()), 0.001f, 100.0f));
		m_Camera->setUp({ 0.0f, 1.0f, 0.0f });
	}

	void OnUpdate() override
	{
		WLD::Graphics::Renderer::Renderer::BeginScene(m_Camera);
		m_BackgroundShader->Bind();
		std::dynamic_pointer_cast<WLD::Graphics::OpenGL::OpenGLShader>(m_BackgroundShader)->SetUniformFloat3("u_Colour", m_SetColour);
		WLD::Graphics::Renderer::Renderer::Submit(m_BackgroundVA, m_BackgroundShader);
		WLD::Graphics::Renderer::Renderer::Submit(m_BackgroundVA, m_TextureShader);

		std::pair<LONG, LONG> rotation = getRotation();
		m_Camera->setFront({toFloat(rotation.first / 2.0), toFloat(rotation.second / 2.0), 0.0f});
		m_Camera->setPos(getMovement(m_CamSpeed));
		
		for (float i = -2.0f; i < 3.0f; i += 1.0f)
			for (float j = -2.0f; j < 3.0f; j += 1.0f)
			{
				glm::vec3 translation(i * 1.1f, 0.0f, j * 1.1f);
				glm::mat4 transform(glm::translate(glm::mat4(1.0f), translation));
				WLD::Graphics::Renderer::Renderer::Submit(m_MultiColourVertexArray, m_MultiColourShader, transform);
			}
		WLD::Graphics::Renderer::Renderer::EndScene();
	}

	void OnImGuiDraw() override
	{
		static glm::vec3 pos(0.0f);
		static glm::vec3 rot(0.0f);

		ImGui::Begin("3D Object");
		ImGui::Text("Rotation");
		ImGui::SliderFloat3("x, y, z", glm::value_ptr(rot), -180.0f, 180.0f);
		ImGui::Separator();
		ImGui::Text("Position");
		ImGui::SliderFloat3("x, y, z ", glm::value_ptr(pos), -10.0f, 10.0f);
		ImGui::End();

		ImGui::Begin("Camera");
		ImGui::Text("Speed");
		ImGui::SliderFloat("speed", &m_CamSpeed, 0.0f, 10.0f, "%.1f");
		ImGui::End();

		ImGui::Begin("Background");
		ImGui::Text("Colour");
		ImGui::ColorEdit3("colour", glm::value_ptr(m_SetColour));
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

		float deltaTime = WLD::Time::GetDeltaTime();

		if (WLD::Input::IsKeyPressed(WLD_KEY_W)) x += speed * deltaTime;
		if (WLD::Input::IsKeyPressed(WLD_KEY_S)) x -= speed * deltaTime;
		if (WLD::Input::IsKeyPressed(WLD_KEY_R)) y += speed * deltaTime;
		if (WLD::Input::IsKeyPressed(WLD_KEY_F)) y -= speed * deltaTime;
		if (WLD::Input::IsKeyPressed(WLD_KEY_D)) z += speed * deltaTime;
		if (WLD::Input::IsKeyPressed(WLD_KEY_A)) z -= speed * deltaTime;

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
	WLD::Ref<WLD::Graphics::Renderer::Shader> m_MultiColourShader;
	WLD::Ref<WLD::Graphics::Renderer::VertexArray> m_MultiColourVertexArray;

	WLD::Ref<WLD::Graphics::Renderer::Shader> m_BackgroundShader;
	WLD::Ref<WLD::Graphics::Renderer::Shader> m_TextureShader;
	WLD::Ref<WLD::Graphics::Renderer::VertexArray> m_BackgroundVA;

	WLD::Ref<WLD::Graphics::Camera::PerspectiveCamera> m_Camera;

	float m_CamSpeed;
	glm::vec3 m_SetColour = { 255.0f/255.0f, 105.0f/255.0f, 180.0f/255.0f };
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
	if (argc > 1 && !run[2] && !run[3])
	{
		if (!strcmp(argv[1], "-opengl"))
		{
			WLD::Graphics::Renderer::Renderer::SetAPI(WLD::Graphics::Renderer::RendererAPI::API::OpenGL);
			run[2] = true;
		}
		else if (!strcmp(argv[1], "-dx12"))
		{
			WLD::Graphics::Renderer::Renderer::SetAPI(WLD::Graphics::Renderer::RendererAPI::API::DirectX12);
			run[2] = true;
		}
	}

	if (!run[2] || run[3])
	{
		run[3] = false;
		return new SetAPI(run);
	}

	return new SandBox(run);
}
