#include "wldpch.h"
#include "ImGuiLayer.h"
#include "OpenGL/ImGui/VP.h"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_dx12.h"
#include "backends/imgui_impl_win32.h"

#include "application.h"
#include "RendererAPI.h"

#include "DX12/Context.h"

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)


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
		bool* run = app.GetRun();
		auto& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()));
		
		ImGui::Begin("test");
		ImGui::Text("FPS %.3f ms/frame (%.1f FPS)", Time::GetFrameTime_ms(), Time::GetFPS());
		if (run[2])
		{
			bool VSync = window.IsVSync();
			ImGui::Checkbox("VSync", &VSync);
			run[3] = ImGui::Button("Reset API");

			if (VSync != window.IsVSync())
				window.SetVSync(VSync);
		}
		ImGui::End();

		if (run[3])
		{
			run[0] = false;
			run[1] = true;
			run[2] = false;
		}
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
		ImGui_ImplX_RenderDrawData();

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			window.GetNativeGraphicsContext().MakeCurrent();
		}
	}

//private:
	void ImGuiLayer::OpenGLInit()
	{
		HWND window = Application::Get().GetWindow().GetNativeWindow();
		auto& io = ImGui::GetIO();

		// Setup Platform/Renderer bindings
		ImGui_ImplWin32_InitForOpenGL(window);
		ImGui_ImplOpenGL3_Init();

		ImGui_ImplX_NewFrame = ImGui_ImplOpenGL3_NewFrame;
		std::function<void()> func([&]() { OpenGLRenderDrawData(); });
		ImGui_ImplX_RenderDrawData.swap(func);

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGuiPlatformIO& platform_io = ImGui::GetPlatformIO();
			WLD_CORE_ASSERT(!platform_io.Renderer_CreateWindow, "ImGUi Renderer_CreateWindow is not NULL");
			WLD_CORE_ASSERT(!platform_io.Renderer_DestroyWindow, "ImGUi Renderer_DestroyWindow is not NULL");
			WLD_CORE_ASSERT(!platform_io.Renderer_SwapBuffers, "ImGUi Renderer_SwapBuffers is not NULL");
			WLD_CORE_ASSERT(!platform_io.Platform_RenderWindow, "ImGUi Platform_RenderWindow is not NULL");
			platform_io.Renderer_CreateWindow = ImGuiVP::CreateVPWindow;
			platform_io.Renderer_DestroyWindow = ImGuiVP::DestroyVPWindow;
			platform_io.Renderer_SwapBuffers = ImGuiVP::SwapVPBuffers;
			platform_io.Platform_RenderWindow = ImGuiVP::RenderVPWindow;
		}
	}

	void ImGuiLayer::DX12Init()
	{
		Window& window = Application::Get().GetWindow();
		HWND hwnd = window.GetNativeWindow();
		Graphics::dx12::DX12Context& graphicContext = (Graphics::dx12::DX12Context&)window.GetNativeGraphicsContext();
		ID3D12Device* pd3dDevice = graphicContext.GetDevice();
		ID3D12DescriptorHeap* pd3dSrvDescHeap = graphicContext.GetSrvDescHeap();

		ImGui_ImplWin32_Init(hwnd);
		ImGui_ImplDX12_Init(pd3dDevice, graphicContext.GetNumBackBuffers(), DXGI_FORMAT_R8G8B8A8_UNORM, pd3dSrvDescHeap, pd3dSrvDescHeap->GetCPUDescriptorHandleForHeapStart(), pd3dSrvDescHeap->GetGPUDescriptorHandleForHeapStart());

		ImGui_ImplX_NewFrame = ImGui_ImplDX12_NewFrame;
		std::function<void()> func([&]() { DX12RenderDrawData(); });
		ImGui_ImplX_RenderDrawData.swap(func);

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
		case Graphics::Renderer::RendererAPI::API::DirectX12:
			DX12Init(); return;
		}
	}

	void ImGuiLayer::APIShutdown()
	{
		switch (Graphics::Renderer::RendererAPI::GetAPI())
		{
		case Graphics::Renderer::RendererAPI::API::OpenGL:
			OpenGLShutdown(); return;
		case Graphics::Renderer::RendererAPI::API::DirectX12:
			DX12Shutdown(); return;
		}
	}

	void ImGuiLayer::DX12RenderDrawData()
	{
		Graphics::dx12::DX12Context& graphicContext = (Graphics::dx12::DX12Context&)Application::Get().GetWindow().GetNativeGraphicsContext();

		ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), graphicContext.GetCommandList());
	}

	void ImGuiLayer::OpenGLRenderDrawData()
	{
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	bool ImGuiLayer::OnWindowResize(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(static_cast<float>(app.GetWindow().GetWidth()), static_cast<float>(app.GetWindow().GetHeight()));
		return true;
	}
}
