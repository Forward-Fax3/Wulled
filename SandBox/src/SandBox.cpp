#define ENTRY_POINT
#include "App.h"
#include "apiset.h"
#include "Engine/src/Core/Log.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

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
		: Layer("Render"), m_CamSpeed(10.0f)
	{
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

		std::vector<WLD::InputShader> shaders;
		shaders.reserve(2);
		shaders.emplace_back(WLD::WLD_ShaderType::Vertex, "multiColour.vert");
		shaders.emplace_back(WLD::WLD_ShaderType::Fragment, "multiColour.frag");

		m_MultiColourShader.reset(WLD::Shader::Create(shaders));

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
		m_Camera->SetUp({ 0.0f, 1.0f, 0.0f });

		// background camera creation
//		m_BackgroundCamera.reset(CreateMemory(WLD::Camera::PerspectiveCamera, 1.0f, toFloat(window.GetHeight()), toFloat(window.GetWidth()), 0.3f, 1000.0f));
//		m_BackgroundCamera->setUp({ 0.0f, 1.0f, 0.0f });
	}

	~ExampleLayer()
	{
	}

	void OnUpdate() override
	{
		m_Camera->SetPos(getMovement(m_CamSpeed));
		m_Camera->SetFront(getRotation() * 0.5f);
		WLD::Renderer::BeginScene(m_Camera);
		WLD::Renderer::SetBackgroundColour(glm::vec4(m_SetColour, 1.0f));

		WLD::Renderer::SetShader(m_MultiColourShader);
		
		for (int64_t i = -2; i < 3; i++)
			for (int64_t j = -2; j < 3; j++)
				for (int64_t k = -2; k < 3; k++)
				{
					glm::vec4 color = { 1.0f * ((float)k + 2.0f) * 0.2f, 1.0f * ((float)j + 2.0f) * 0.2f, 1.0f * ((float)i + 2.0f) * 0.2f , 1.0f};

					glm::vec3 translation(i * 1.1f, k * 1.1f, j * 1.1f);
					WLD::Renderer::DrawCube(translation, glm::vec3(10.0f), color);
				}

		WLD::Renderer::EndScene();
	}

	void OnImGuiDraw() override
	{
		static glm::vec3 pos(0.0f);
		static glm::vec3 rot(0.0f);
		bool activateCat = false;
		bool backgroundEvent = true;
		bool wireFrameEvent = false;
		static uint8_t PreviousFOV = m_FOV;

		ImGui::Begin("3D Object");
		ImGui::Text("Rotation");
		ImGui::SliderFloat3("x, y, z", glm::value_ptr(rot), -180.0f, 180.0f);
		ImGui::Separator();
		ImGui::Text("Position");
		ImGui::SliderFloat3("x, y, z ", glm::value_ptr(pos), -10.0f, 10.0f); // added a space at the end of the string to give if a unique name/ID to prevent it from linking to the rotation slider
		ImGui::End();

		ImGui::Begin("Camera");
		ImGui::Text("Speed");
		float camSpeedTemp = m_CamSpeed / 10.0f;
		ImGui::SliderFloat("speed", &camSpeedTemp, 0.1f, 10.0f, "%.1f");
		m_CamSpeed = camSpeedTemp * 10.0f;
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

		m_Camera->SetPosition(pos);
		m_Camera->SetRotation(rot);

		if (activateCat)
		{
			static bool isCat = false;
			WLD::Application& m_App = WLD::Application::Get();

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
			m_Camera->SetProjection(toFloat(m_FOV), toFloat(WLD::Application::Get().GetWindow().GetHeight()), toFloat(WLD::Application::Get().GetWindow().GetWidth()), 0.3f, 1000.0f);
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

		for (const auto& key : m_Keys)
			switch (key)
			{
			case WLD_KEY_W: x += speed * deltaTime; break;
			case WLD_KEY_S: x -= speed * deltaTime; break;
			case WLD_KEY_R: y += speed * deltaTime; break;
			case WLD_KEY_F: y -= speed * deltaTime; break;
			case WLD_KEY_D: z += speed * deltaTime; break;
			case WLD_KEY_A: z -= speed * deltaTime; break;
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
		m_Camera->SetProjection(45.0f, toFloat(e.GetHeight()), toFloat(e.GetWidth()), 0.3f, 1000.0f);
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
			m_Camera->SetProjection(toFloat(--m_FOV), toFloat(WLD::Application::Get().GetWindow().GetHeight()), toFloat(WLD::Application::Get().GetWindow().GetWidth()), 0.3f, 1000.0f);
		}
		else if (e.GetYOffset() < 0 && m_FOV < 179)
		{
			m_Camera->SetProjection(toFloat(++m_FOV), toFloat(WLD::Application::Get().GetWindow().GetHeight()), toFloat(WLD::Application::Get().GetWindow().GetWidth()), 0.3f, 1000.0f);
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
