#define ENTRY_FILE
#include "app.h"
#include "apiset.h"
#include "Engine/src/core/Log.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>
#include <concurrent_vector.h>

#define toFloat(x) static_cast<float>(x)


class catLayer : public WLD::Layer
{
	public:
	catLayer(WLD::Ref<WLD::VertexArray> BackgroundVA, WLD::Ref<WLD::Camera::PerspectiveCamera> Camera)
		: Layer("cat"), m_BackgroundVA(BackgroundVA), m_Camera(Camera)
	{
//		m_Texture.reset(WLD::Texture2D::Create("assets/textures/cat.png"));
//
//		m_TextureShader.reset(WLD::Shader::Create("assets/indevidualShaders/Texture.glsl"));
//		m_TextureShader->Bind();
//		((WLD::OpenGL::OpenGLShader*)m_TextureShader.get())->SetUniformInt("u_Texture", 0);
	}

	~catLayer()
	{
	}

	void OnUpdate() override
	{
//		WLD::Renderer::BeginScene(m_Camera);
//		m_Texture->Bind();
//		WLD::Renderer::Submit(m_BackgroundVA, m_TextureShader, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 98.00f)));
//		WLD::Renderer::EndScene();
	}

private:
	WLD::Ref<WLD::Texture2D> m_Texture;
	WLD::Ref<WLD::Shader> m_TextureShader;
	WLD::Ref<WLD::VertexArray> m_BackgroundVA;

	WLD::Ref<WLD::Camera::PerspectiveCamera> m_Camera;
};

class ExampleLayer : public WLD::Layer
{
public:
	ExampleLayer()
		: Layer("Render"), m_CamSpeed(1.0f)
	{
		// multicolour squire data
//		float multiColourVertices[] =
//		{
//			-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
//			-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 1.0f,
//			 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
//			 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
//			 0.0f,  0.0f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,
//													   
//			-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
//			 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
//			 0.0f,  0.5f, -0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//		};
//
//		uint32_t multiColourIndices[] =
//		{
//			0, 1, 4,
//			1, 2, 4,
//			2, 3, 4,
//			3, 0, 4,
//
//			2, 1, 7,
//			1, 5, 7,
//			5, 6, 7,
//			6, 2, 7,
//		};

		// background data
//		float backgroundVertices[] =
//		{
//			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
//			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
//			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
//			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f
//		};
//
//		uint32_t backgroundIndices[] =
//		{
//			0, 1, 2,
//			2, 3, 0
//		};
//
//		std::string_view backgroundVertexSrc =
//		R"(
//			#version 460 core
//			
//			layout(location = 0) in vec3 a_Position;
//
//			uniform mat4 u_MVP;
//			uniform mat4 u_Transform;
//			
//			void main()
//			{
//				gl_Position = u_MVP * u_Transform * vec4(a_Position, 1.0);
//			}
//		)";
//
//		std::string_view backgroundFragmentSrc =
//		R"(
//			#version 460 core
//			
//			layout(location = 0) out vec4 colour;
//			
//			uniform vec3 u_Colour;
//
//			void main()
//			{
//				colour = vec4(u_Colour, 1.0f);
//			}
//		)";

		// Vertex buffer and index buffer creation
//		WLD::Ref<WLD::VertexBuffer> vertexBuffer;
//		WLD::Ref<WLD::IndexBuffer> indexBuffer;

		// multicolour squire creation
//		WLD::InputShader indevidualShaders[] = { {}, {} };
//		indevidualShaders[0].type = WLD::ShaderType::Vertex;
//		indevidualShaders[0].isFromFile = true;
//		indevidualShaders[0].source = "multiColour.vert";
//		indevidualShaders[0].isCompiled = false;
//
//		indevidualShaders[1].type = WLD::ShaderType::Fragment;
//		indevidualShaders[1].isFromFile = true;
//		indevidualShaders[1].source = "multiColour.frag";
//		indevidualShaders[1].isCompiled = false;
//
//		WLD::InputShaders shaders = {};
//		shaders.numberOfShaders = 2;
//		shaders.shaders = indevidualShaders;

		std::vector<WLD::InputShader> shaders;
		shaders.reserve(2);
		shaders.emplace_back(WLD::WLD_ShaderType::Vertex, "multiColour.vert");
		shaders.emplace_back(WLD::WLD_ShaderType::Fragment, "multiColour.frag");

		m_MultiColourShader.reset(WLD::Shader::Create(shaders));
//		m_MultiColourVertexArray.reset(WLD::VertexArray::Create());
//
//		vertexBuffer.reset(WLD::VertexBuffer::Create(multiColourVertices, sizeof(multiColourVertices)));
//		indexBuffer.reset(WLD::IndexBuffer::Create(multiColourIndices, sizeof(multiColourIndices) / sizeof(uint32_t)));
//
//		vertexBuffer->SetLayout
//		({
//			{ WLD::ShaderDataType::Float3, "a_Position" },
//			{ WLD::ShaderDataType::Float4, "a_Colour" }
//		});
//
//		m_MultiColourVertexArray->AddVertexBuffer(vertexBuffer);
//		m_MultiColourVertexArray->SetIndexBuffer(indexBuffer);

		// background creation
//		m_BackgroundShader.reset(WLD::Shader::Create(backgroundVertexSrc, backgroundFragmentSrc));
//		m_BackgroundVA.reset(WLD::VertexArray::Create());
//
//		vertexBuffer.reset(WLD::VertexBuffer::Create(backgroundVertices, sizeof(backgroundVertices)));
//		indexBuffer.reset(WLD::IndexBuffer::Create(backgroundIndices, sizeof(backgroundIndices) / sizeof(uint32_t)));
//
//		vertexBuffer->SetLayout
//		({
//			{ WLD::ShaderDataType::Float3, "a_Position" },
//			{ WLD::ShaderDataType::Float2, "a_TexCoord" }
//		});

//		m_BackgroundVA->AddVertexBuffer(vertexBuffer);
//		m_BackgroundVA->SetIndexBuffer(indexBuffer);

		// camera creation
		WLD::Window& window = WLD::Application::Get().GetWindow();
		m_Camera.reset(CreateMemory(WLD::Camera::PerspectiveCamera, m_FOV, toFloat(window.GetHeight()), toFloat(window.GetWidth()), 0.3f, 1000.0f));
		m_Camera->setUp({ 0.0f, 1.0f, 0.0f });

		// background camera creation
//		m_BackgroundCamera.reset(CreateMemory(WLD::Camera::PerspectiveCamera, 1.0f, toFloat(window.GetHeight()), toFloat(window.GetWidth()), 0.3f, 1000.0f));
//		m_BackgroundCamera->setUp({ 0.0f, 1.0f, 0.0f });
	}

	~ExampleLayer()
	{
	}

//	void OnUpdate() override
//	{
//		static bool hasRrintedMat4 = false;
//		if (m_BackGround)
//		{
//			WLD::Renderer::BeginScene(m_BackgroundCamera);
//			m_BackgroundShader->Bind();
//			((WLD::OpenGL::OpenGLShader*)m_BackgroundShader.get())->SetUniformFloat3("u_Colour", m_SetColour);
//			glm::mat4 scale(glm::scale(glm::mat4(1.0f), glm::vec3(0.0f, 900.0f, 900.0f)));
//			glm::mat4 transform(glm::translate(scale, glm::vec3(900.0f, 0.0f, 0.0f)));
//
//			if (!hasRrintedMat4)
//			{
//				for (int i = 0; i < 4; i++)
//					for (int j = 0; j < 4; j++)
//					{
//						LOG_INFO("(m_BackgroundCamera->getProjection() * transform)[{0}][{1}] = {2}", i, j, (m_BackgroundCamera->getProjection() * transform)[i][j]);
//						LOG_INFO("transform[{0}][{1}]                                         = {2}", i, j, transform[i][j]);
//						LOG_INFO("m_BackgroundCamera->getProjection()[{0}][{1}]               = {2}", i, j, m_BackgroundCamera->getProjection()[i][j]);
//						LOG_INFO("scale[{0}][{1}]                                             = {2}", i, j, scale[i][j]);
//						LOG_INFO("");
//					}
//				hasRrintedMat4 = true;
//			}
//
//			WLD::Renderer::Submit(m_BackgroundVA, m_BackgroundShader, transform);
//			WLD::Renderer::EndScene();
//		}
//
//		WLD::Renderer::BeginScene(m_Camera);
//		glm::vec2 rotation = getRotation();
//		m_Camera->setFront(rotation * 0.5f);
//		m_Camera->setPos(getMovement(m_CamSpeed));
//		glm::mat4 scale(glm::scale(glm::mat4(1.0f), glm::vec3(10)));
//
//		for (float i = -2.0f; i < 3.0f; i += 1.0f)
//			for (float j = -2.0f; j < 3.0f; j += 1.0f)
//			{
//				glm::vec3 translation(i * 1.1f, 0.0f, j * 1.1f);
//				glm::mat4 transform(glm::translate(scale, translation));
//				WLD::Renderer::Submit(m_MultiColourVertexArray, m_MultiColourShader, transform);
//			}
//		WLD::Renderer::EndScene();
//	}

	void OnUpdate()
	{
		WLD::Renderer::BeginScene(m_Camera);
		m_Camera->setPos(getMovement(m_CamSpeed));
		m_Camera->setFront(getRotation() * 0.5f);
		WLD::Renderer::SetBackgroundColour(glm::vec4(m_SetColour, 1.0f));

		WLD::Renderer::SetShader(m_MultiColourShader);

		for (float i = -2.0f; i < 3.0f; i += 1.0f)
			for (float j = -2.0f; j < 3.0f; j += 1.0f)
			{
				glm::vec4 color = { 1.0f, 1.0f * (j + 2.0f) * 1 / 5, 1.0f * (i + 2.0f) * 1 / 5 , 1.0f};

				glm::vec3 translation(i * 1.1f, 0.0f, j * 1.1f);
				WLD::Renderer::DrawCube(translation, glm::vec3(10.0f), color);
			}

		WLD::Renderer::EndScene();
	}

	void OnImGuiDraw() override
	{
		static glm::vec3 pos(0.0f);
		static glm::vec3 rot(0.0f);
		static bool isCat = false;
		bool activateCat = false;
		bool backgroundEvent = true;
		bool wireFrameEvent = false;
		static uint8_t PreviousFOV = m_FOV;
		WLD::Application& m_App = WLD::Application::Get();

		ImGui::Begin("3D Object");
		ImGui::Text("Rotation");
		ImGui::SliderFloat3("x, y, z", glm::value_ptr(rot), -180.0f, 180.0f);
		ImGui::Separator();
		ImGui::Text("Position");
		ImGui::SliderFloat3("x, y, z ", glm::value_ptr(pos), -10.0f, 10.0f);
		ImGui::End();

		ImGui::Begin("Camera");
		ImGui::Text("Speed");
		ImGui::SliderFloat("speed", &m_CamSpeed, 0.1f, 10.0f, "%.1f");
		ImGui::Separator();
		ImGui::Text("FOV");
		int FOV = m_FOV;
		ImGui::SliderInt("fov", &FOV, 1, 179);
		m_FOV = FOV;
		ImGui::End();

		ImGui::Begin("Background");
		ImGui::Separator();
//		ImGui::Text("This is broken at the moment");
		ImGui::Separator();
		ImGui::Text("Colour");
		ImGui::ColorEdit3("colour", glm::value_ptr(m_SetColour));
//		backgroundEvent = ImGui::Button((!m_BackGround) ? "Enable Background" : "Disable Background");
		ImGui::End();

//		ImGui::Begin("cat layer");
//		ImGui::Separator();
//		ImGui::Text("This is broken at the moment");
//		ImGui::Separator();
//		activateCat = ImGui::Button((!isCat) ? "enable cat" : "disable cat");
//		ImGui::Text("The Great cat-ining :3");
//		ImGui::Text("Meow-ha-ha-haar. :3");
//		ImGui::End();

		ImGui::Begin("API");
		wireFrameEvent = ImGui::Button("Toggle Wireframe");
		ImGui::End();

		if (wireFrameEvent)
			WLD::RenderCommand::ToggleWireFrame();

		m_Camera->setPosition(pos);
		m_Camera->setRotation(rot);

		if (activateCat)
		{
			if (!isCat)
			{
				m_CatLayer = CreateMemory(catLayer, m_BackgroundVA, m_Camera);
				m_App.PushLayer(m_CatLayer);
			}
			else
			{
				m_App.PopLayer(m_CatLayer);
				m_CatLayer = nullptr;
			}
			isCat = !isCat;
		}

		if (backgroundEvent)
			m_BackGround = !m_BackGround;

		if (m_FOV != PreviousFOV)
		{
			m_Camera->setProjection(toFloat(m_FOV), toFloat(WLD::Application::Get().GetWindow().GetHeight()), toFloat(WLD::Application::Get().GetWindow().GetWidth()), 0.3f, 1000.0f);
			PreviousFOV = m_FOV;
		}
	}

	void OnEvent(WLD::Event& e) override
	{
		WLD::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WLD::WindowResizeEvent>(BIND_EVENT_FN(ExampleLayer::OnWindowResize));
		dispatcher.Dispatch<WLD::KeyPressedEvent>(BIND_EVENT_FN(ExampleLayer::OnKeyPressed));
		dispatcher.Dispatch<WLD::KeyReleasedEvent>(BIND_EVENT_FN(ExampleLayer::OnKeyReleased));
		dispatcher.Dispatch<WLD::MouseMovedEvent>(BIND_EVENT_FN(ExampleLayer::OnMouseMoved));
		dispatcher.Dispatch<WLD::MouseButtonPressedEvent>(BIND_EVENT_FN(ExampleLayer::OnMouseButtonPressed));
		dispatcher.Dispatch<WLD::MouseButtonReleasedEvent>(BIND_EVENT_FN(ExampleLayer::OnMouseButtonReleased));
		dispatcher.Dispatch<WLD::MouseScrolledEvent>(BIND_EVENT_FN(ExampleLayer::OnMouseScroll));
	}

private:
	glm::vec3 getMovement(float speed)
	{
		float x = 0.0f, y = 0.0f, z = 0.0f;

		float deltaTime = WLD::Time::GetDeltaTime();

		for (auto key : m_Keys)
		{
			if (key == WLD_KEY_W) x += speed * deltaTime * 10;
			if (key == WLD_KEY_S) x -= speed * deltaTime * 10;
			if (key == WLD_KEY_R) y += speed * deltaTime * 10;
			if (key == WLD_KEY_F) y -= speed * deltaTime * 10;
			if (key == WLD_KEY_D) z += speed * deltaTime * 10;
			if (key == WLD_KEY_A) z -= speed * deltaTime * 10;
		}

		return { x, y, z };
	}

	glm::vec2 getRotation()
	{
		static glm::vec2 lastPos = m_MousePos;
		static glm::vec2 total = { 0.0f, 0.0f };
		glm::vec2 delta = m_MousePos - lastPos;

		if (std::find(m_MouseButtons.begin(), m_MouseButtons.end(), WLD_MOUSE_BUTTON_RIGHT) != m_MouseButtons.end() ||
			std::find(m_Keys.begin(), m_Keys.end(), WLD_KEY_LEFT_CONTROL) != m_Keys.end())
			total += glm::vec2(1.0f, -1.0f) * delta;

//		     if (total.first  < -360)  total.first  += 720;
//		else if (total.first  >  360)  total.first  -= 720;
//		     if (total.second < -360)  total.second += 720;
//		else if (total.second >  360)  total.second -= 720;

		lastPos = m_MousePos;
		return total;
	}

	bool OnWindowResize(WLD::WindowResizeEvent& e)
	{
		m_Camera->setProjection(45.0f, toFloat(e.GetHeight()), toFloat(e.GetWidth()), 0.3f, 1000.0f);
		return true;
	}

	bool OnKeyPressed(WLD::KeyPressedEvent& e)
	{
		if (std::find(m_Keys.begin(), m_Keys.end(), e.GetKeyCode()) == m_Keys.end())
			m_Keys.push_back(e.GetKeyCode());
		return true;
	}
	
	bool OnKeyReleased(WLD::KeyReleasedEvent& e)
	{
		m_Keys.erase(std::remove(m_Keys.begin(), m_Keys.end(), e.GetKeyCode()), m_Keys.end());
		return true;
	}

	bool OnMouseButtonPressed(WLD::MouseButtonPressedEvent& e)
	{
		if (std::find(m_MouseButtons.begin(), m_MouseButtons.end(), e.GetMouseButton()) == m_MouseButtons.end())
			m_MouseButtons.push_back(e.GetMouseButton());
		return true;
	}

	bool OnMouseButtonReleased(WLD::MouseButtonReleasedEvent& e)
	{
		m_MouseButtons.erase(std::remove(m_MouseButtons.begin(), m_MouseButtons.end(), e.GetMouseButton()), m_MouseButtons.end());
		return true;
	}

	bool OnMouseMoved(WLD::MouseMovedEvent& e)
	{
		m_MousePos = { e.GetX(), e.GetY() };
		return true;
	}

	bool OnMouseScroll(WLD::MouseScrolledEvent& e)
	{
		if (e.GetYOffset() > 0 && m_FOV > 1)
		{
			m_Camera->setProjection(toFloat(--m_FOV), toFloat(WLD::Application::Get().GetWindow().GetHeight()), toFloat(WLD::Application::Get().GetWindow().GetWidth()), 0.3f, 1000.0f);
		}
		else if (e.GetYOffset() < 0 && m_FOV < 179)
		{
			m_Camera->setProjection(toFloat(++m_FOV), toFloat(WLD::Application::Get().GetWindow().GetHeight()), toFloat(WLD::Application::Get().GetWindow().GetWidth()), 0.3f, 1000.0f);
		}
		return true;
	}

private:
	WLD::Ref<WLD::Shader> m_MultiColourShader;
	WLD::Ref<WLD::VertexArray> m_MultiColourVertexArray;

	WLD::Ref<WLD::Shader> m_BackgroundShader;
	WLD::Ref<WLD::VertexArray> m_BackgroundVA;

	WLD::Ref<WLD::Camera::PerspectiveCamera> m_Camera, m_BackgroundCamera;
	float m_CamSpeed;
	std::atomic<uint8_t> m_FOV = 45;

	WLD::Layer* m_CatLayer = nullptr;

	glm::vec3 m_SetColour = { 255.0f/255.0f, 105.0f/255.0f, 180.0f/255.0f };

	bool m_BackGround = false;

	std::vector<uint32_t> m_Keys, m_MouseButtons;
	glm::vec2 m_MousePos = glm::vec2(0.0f);
};

class BaseLayer : public WLD::Layer
{
public:
	BaseLayer(bool* run)
		: Layer("base"), m_Run(run), m_App(WLD::Application::Get())
	{
		if (!m_Run[2])
		{
			m_ActiveLayer = CreateMemory(SetAPILayer, "SetAPILayer");
			m_PrevLayer = Layers::setAPI;
		}
		else
		{
			m_ActiveLayer = CreateMemory(ExampleLayer);
			m_PrevLayer = Layers::example;
		}
		m_App.PushLayer(m_ActiveLayer);
	}

	~BaseLayer()
	{
	}

	void OnUpdate() override
	{
		if (m_Run[3])
		{
			auto NextAPI = WLD::Renderer::GetNextAPI();
			auto CurrentAPI = WLD::Renderer::GetAPI();

			if (NextAPI == CurrentAPI)
			{
				if (m_PrevLayer == Layers::setAPI)
				{
					m_App.PopLayer(m_ActiveLayer);
					m_ActiveLayer = CreateMemory(ExampleLayer);
					m_PrevLayer = Layers::example;
					m_App.PushLayer(m_ActiveLayer);
					m_Run[2] = true;
					m_Run[3] = false;
				}
				else
				{
					m_App.PopLayer(m_ActiveLayer);
					m_ActiveLayer = CreateMemory(SetAPILayer, "SetAPILayer");
					m_PrevLayer = Layers::setAPI;
					m_App.PushLayer(m_ActiveLayer);
					m_Run[2] = false;
					m_Run[3] = false;
				}
			}
			else
			{
				m_Run[0] = false;
				m_Run[1] = true;
				m_Run[2] = false;
			}
		}
	}

private:
	enum class Layers
	{
		setAPI,
		example
	};

	bool* m_Run; // 0 - run, 1 - restart, 2 - APISet, 3 - APIReset
	WLD::Layer* m_ActiveLayer;
	WLD::Application& m_App;
	Layers m_PrevLayer;
};

class SandBox : public WLD::Application
{
public:
	SandBox(bool* run)
		: Application(run)
	{
		std::cout << "sand box created" << std::endl;
//		PushLayer(CreateMemory(BaseLayer, run));
		PushLayer(CreateMemory(ExampleLayer));
	}

	~SandBox()
	{
		std::cout << "sand box destroyed" << std::endl;
	}
};

WLD::Application* WLD::CreateApplication(bool* run, int argc, char** argv)
{
//	if (argc > 1 && !run[2] && !run[3])
//	{
//		if (!strcmp(argv[1], "-opengl"))
//		{
//			WLD::Renderer::SetAPI(WLD::RendererAPI::API::OpenGL);
//			run[2] = true;
//		}
//		else if (!strcmp(argv[1], "-dx12"))
//		{
//			WLD::Renderer::SetAPI(WLD::RendererAPI::API::DirectX12);
//			run[2] = true;
//		}
//	}
//
//	if (!run[2] || run[3])
//	{
//		run[3] = false;
//		return CreateMemory(SetAPI, run);
//	}

	return CreateMemory(SandBox, run);
}
