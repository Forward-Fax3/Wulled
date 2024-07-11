#include "WLDPCH.h"
#include "ImGuiLayer.h"
#include "OpenGLImGui/VP.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"

#include "Application.h"
#include "RendererAPI.h"

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)


namespace WLD
{
//public:
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
	} 

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		ImGuiIO& io = ImGui::GetIO();

		// Setup Dear ImGui context
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StylecoloursClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application::Get().GetWindow().GetGraphicsContext().ImGuiInit();
	}

	void ImGuiLayer::OnDetach()
	{
		Application::Get().GetWindow().GetGraphicsContext().ImGuiShutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyPlatformWindows();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnImGuiDraw()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		Window& window = app.GetWindow();
		bool* run = app.GetRun(); // 0 - run, 1 - restart, 2 - APISet, 3 - APIReset
		io.DisplaySize = ImVec2(static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()));
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
		Application::Get().GetWindow().GetGraphicsContext().ImGuiBegin();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::end()
	{
		ImGuiIO& io = ImGui::GetIO();

		// Rendering
		ImGui::Render();
		Application::Get().GetWindow().GetGraphicsContext().ImGuiEnd();

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			Application::Get().GetWindow().GetGraphicsContext().MakeCurrent();
		}
	}

//private:
	bool ImGuiLayer::OnWindowResize(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		Window& window = Application::Get().GetWindow();
		io.DisplaySize = ImVec2(static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()));
		return true;
	}
}
