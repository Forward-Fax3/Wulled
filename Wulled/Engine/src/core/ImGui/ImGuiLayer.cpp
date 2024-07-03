#include "wldpch.h"
#include "ImGuiLayer.h"
#include "OpenGLImGui/VP.h"

#include "imgui.h"
#include "backends/imgui_impl_SDL2.h"

#include "application.h"
#include "RendererAPI.h"

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)


namespace WLD
{
//public:
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer"), m_Context(Application::Get().GetWindow().GetGraphicsContext()), m_io(init())
	{
	} 

	ImGuiLayer::~ImGuiLayer()
	{
	}

	ImGuiIO& ImGuiLayer::init()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		return ImGui::GetIO();
	}

	void ImGuiLayer::OnAttach()
	{
		// Setup Dear ImGui context
		m_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//m_io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		m_io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		m_io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//m_io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//m_io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StylecoloursClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (m_io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		m_Context.ImGuiInit();
	}

	void ImGuiLayer::OnDetach()
	{
		m_Context.ImGuiShutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyPlatformWindows();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnImGuiDraw()
	{
		Application& app = Application::Get();
		Window& window = app.GetWindow();
		bool* run = app.GetRun(); // 0 - run, 1 - restart, 2 - APISet, 3 - APIReset
		m_io.DisplaySize = ImVec2(static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()));
		bool APIReset = false;
		
		ImGui::Begin("test");
		ImGui::Text("FPS %.3f ms/frame (%.1f FPS)", Time::GetFrameTime_ms(), Time::GetFPS());
		if (run[2])
		{
			bool VSync = window.IsVSync();
			ImGui::Checkbox("VSync", &VSync);
			APIReset = ImGui::Button("Reset API");

			if (VSync != window.IsVSync())
				window.SetVSync(VSync);
		}
		bool exit = ImGui::Button("exit");
		bool restart = ImGui::Button("restart");
		bool restartWithAPIReset = ImGui::Button("restart/API reset");
		ImGui::End();

		if (exit)
		{
			run[0] = false;
		}

		if (restart)
		{
			run[0] = false;
			run[1] = true;
		}

		if (restartWithAPIReset)
		{
			run[0] = false;
			run[1] = true;
			run[2] = false;
			run[3] = false;
		}

		if (APIReset)
		{
			run[2] = false;
			run[3] = true;
		}
	}

	void ImGuiLayer::Begin()
	{
		m_Context.ImGuiBegin();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::end()
	{
		Window& window = Application::Get().GetWindow();

		// Rendering
		ImGui::Render();
		m_Context.ImGuiEnd();

		if (m_io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			m_Context.MakeCurrent();
		}
	}

//private:
	bool ImGuiLayer::OnWindowResize(WindowResizeEvent& e)
	{
		Window& window = Application::Get().GetWindow();
		m_io.DisplaySize = ImVec2(static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()));
		return true;
	}
}
