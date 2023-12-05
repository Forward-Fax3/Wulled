#include "wldpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_dx12.h"
#include "backends/imgui_impl_win32.h"

#include "application.h"
#include "RendererAPI.h"

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

static int const NUM_FRAMES_IN_FLIGHT = 3;
static ID3D12Device* g_pd3dDevice = nullptr;
static ID3D12DescriptorHeap* g_pd3dSrvDescHeap = nullptr;


namespace WLD
{
//public:
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer"), m_io(init())
	{
	} 

	ImGuiLayer::~ImGuiLayer()
	{
		OnDetach();
	}

	ImGuiIO& ImGuiLayer::init()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		return ImGui::GetIO();
	}

	void ImGuiLayer::OnAttach()
	{
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;		    // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		APIInit();
	}

	void ImGuiLayer::OnDetach()
	{
		APIShutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyPlatformWindows();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnImGuiDraw()
	{
		Application& app = Application::Get();
		Window& window = app.GetWindow();
		auto& m_io = ImGui::GetIO();
		m_io.DisplaySize = ImVec2(static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()));
		
		m_io.DeltaTime = static_cast<float>(app.GetDeltaTime());
//		bool VSync = window.IsVSync();
		ImGui::Begin("test");
//		ImGui::Checkbox("VSync", &VSync);
		ImGui::Text("FPS %.3f ms/frame (%.1f FPS)", 1000.0f / m_io.Framerate, m_io.Framerate);
		ImGui::End();

//		if (VSync != window.IsVSync())
//			window.SetVSync(VSync);
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplX_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::end()
	{
		ImGuiIO& io = ImGui::GetIO();
		Window& window = Application::Get().GetWindow();
		io.DisplaySize = ImVec2(static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()));

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			window.GetNativeGraphicsContext().makeCurrent();
		}
	}

//private:
	void ImGuiLayer::OpenGLInit()
	{
		HWND window = Application::Get().GetWindow().GetNativeWindow();

		// Setup Platform/Renderer bindings
		ImGui_ImplWin32_InitForOpenGL(window);
		ImGui_ImplOpenGL3_Init();

		ImGui_ImplX_NewFrame = [&]() { ImGui_ImplOpenGL3_NewFrame(); };
	}

	void ImGuiLayer::DX12Init()
	{
		HWND hwnd = Application::Get().GetWindow().GetNativeWindow();

		ImGui_ImplWin32_Init(hwnd);
//		ImGui_ImplDX12_Init(g_pd3dDevice, NUM_FRAMES_IN_FLIGHT,
//			DXGI_FORMAT_R8G8B8A8_UNORM, g_pd3dSrvDescHeap,
//			g_pd3dSrvDescHeap->GetCPUDescriptorHandleForHeapStart(),
//			g_pd3dSrvDescHeap->GetGPUDescriptorHandleForHeapStart());

		ImGui_ImplX_NewFrame = [&]() { ImGui_ImplDX12_NewFrame(); };

	}

	void ImGuiLayer::OpenGLShutdown()
	{
		ImGui_ImplOpenGL3_Shutdown();
	}

	void ImGuiLayer::DX12Shutdown()
	{
		ImGui_ImplDX12_Shutdown();
	}

	void ImGuiLayer::APIInit()
	{
		switch (Graphics::Renderer::RendererAPI::GetAPI())
		{
		case Graphics::Renderer::RendererAPI::API::OpenGL:
			OpenGLInit(); return;
		case Graphics::Renderer::RendererAPI::API::DX12:
			DX12Init(); return;
		}
	}

	void ImGuiLayer::APIShutdown()
	{
		switch (Graphics::Renderer::RendererAPI::GetAPI())
		{
		case Graphics::Renderer::RendererAPI::API::OpenGL:
			OpenGLShutdown(); return;
		case Graphics::Renderer::RendererAPI::API::DX12:
			DX12Shutdown(); return;
		}
	}

	bool ImGuiLayer::OnWindowResize(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(static_cast<float>(app.GetWindow().GetWidth()), static_cast<float>(app.GetWindow().GetHeight()));
		return true;
	}
}
