#include "wldpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "ImGuiOpenGLRenderer.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "application.h"
#include "WinWindow.h"

#include "Event.h"
#include "ApplicationEvent.h"
#include "KeyEvent.h"
#include "MouseEvent.h"

#include "MouseButtonCodes.h"
#include "KeyCodes.h"


#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace WLD
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer"), m_Time(0.0f), m_io(init())
	{
	} 

	ImGuiLayer::~ImGuiLayer()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyPlatformWindows();
		ImGui::DestroyContext();
	}

	ImGuiIO& ImGuiLayer::init()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		return ImGui::GetIO();
	}

	void ImGuiLayer::OnAttach()
	{
		m_io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		m_io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		
<<<<<<< HEAD
		m_io.KeyMap[ImGuiKey_Tab] = WLD_KEY_TAB;
		m_io.KeyMap[ImGuiKey_LeftArrow] = WLD_KEY_LEFT;
		m_io.KeyMap[ImGuiKey_RightArrow] = WLD_KEY_RIGHT;
		m_io.KeyMap[ImGuiKey_UpArrow] = WLD_KEY_UP;
		m_io.KeyMap[ImGuiKey_DownArrow] = WLD_KEY_DOWN;
		m_io.KeyMap[ImGuiKey_PageUp] = WLD_KEY_PAGE_UP;
		m_io.KeyMap[ImGuiKey_PageDown] = WLD_KEY_PAGE_DOWN;
		m_io.KeyMap[ImGuiKey_Home] = WLD_KEY_HOME;
		m_io.KeyMap[ImGuiKey_End] = WLD_KEY_END;
		m_io.KeyMap[ImGuiKey_Insert] = WLD_KEY_INSERT;
		m_io.KeyMap[ImGuiKey_Delete] = WLD_KEY_DELETE;
		m_io.KeyMap[ImGuiKey_Backspace] = WLD_KEY_BACKSPACE;
		m_io.KeyMap[ImGuiKey_Space] = WLD_KEY_SPACE;
		m_io.KeyMap[ImGuiKey_Enter] = WLD_KEY_ENTER;
		m_io.KeyMap[ImGuiKey_Escape] = WLD_KEY_ESCAPE;

		for (uint8_t i = 0; i < 26; ++i)
			m_io.KeyMap[ImGuiKey_A + i] = WLD_KEY_A + i;
=======
		m_io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		m_io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		m_io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		m_io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		m_io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		m_io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		m_io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		m_io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		m_io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		m_io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		m_io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		m_io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		m_io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		m_io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		m_io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;

		for (uint8_t i = 0; i < 26; ++i)
			m_io.KeyMap[ImGuiKey_A + i] = GLFW_KEY_A + i;
>>>>>>> 6096232c0915328fcc92793c1dda5d2ffdbe916e

		ImGui_ImplOpenGL3_Init("#version 430");
	}

	void ImGuiLayer::OnDetach()
	{
	}

	void ImGuiLayer::OnUpdate()
	{
		Window& window = Application::Get().GetWindow();
		m_io.DisplaySize = ImVec2(window.GetWidth(), window.GetHeight());
		
		float time = (float)glfwGetTime();
		m_io.DeltaTime = m_Time > 0.0f ? (float)(time - m_Time) : (float)(1.0f / 144.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = false;
		ImGui::ShowDemoWindow(&show);

		bool VSync = window.IsVSync();
		ImGui::Begin("test");
		ImGui::Checkbox("VSync", &VSync);
		if (!show)
			show = ImGui::Button("Demo window");
		ImGui::Text("FPS %.3f ms/frame (%.1f FPS)", 1000.0f / m_io.Framerate, m_io.Framerate);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		ImGui::EndFrame();

		if (VSync != window.IsVSync())
			window.SetVSync(VSync);
	}

	void ImGuiLayer::OnEvent(Event& e)
	{		
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		m_io.MouseDown[e.GetMouseButton()] = true;
		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		m_io.MouseDown[e.GetMouseButton()] = false;
		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		m_io.MousePos = ImVec2(e.GetX(), e.GetY());
		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		m_io.MouseWheelH += e.GetXOffset();
		m_io.MouseWheel += e.GetYOffset();

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
<<<<<<< HEAD
		m_io.KeysDown[e.GetKeyCode()] = true;

		m_io.KeyCtrl = m_io.KeysDown[WLD_KEY_LEFT_CONTROL] || m_io.KeysDown[WLD_KEY_RIGHT_CONTROL];
		m_io.KeyAlt = m_io.KeysDown[WLD_KEY_LEFT_ALT] || m_io.KeysDown[WLD_KEY_RIGHT_ALT];
		m_io.KeyShift = m_io.KeysDown[WLD_KEY_LEFT_SHIFT] || m_io.KeysDown[WLD_KEY_RIGHT_SHIFT];
		m_io.KeySuper = m_io.KeysDown[WLD_KEY_LEFT_SUPER] || m_io.KeysDown[WLD_KEY_RIGHT_SUPER];
=======
		m_io.KeysDown[e.GetKeycode()] = true;

		m_io.KeyCtrl = m_io.KeysDown[GLFW_KEY_LEFT_CONTROL] || m_io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		m_io.KeyAlt = m_io.KeysDown[GLFW_KEY_LEFT_ALT] || m_io.KeysDown[GLFW_KEY_RIGHT_ALT];
		m_io.KeyShift = m_io.KeysDown[GLFW_KEY_LEFT_SHIFT] || m_io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		m_io.KeySuper = m_io.KeysDown[GLFW_KEY_LEFT_SUPER] || m_io.KeysDown[GLFW_KEY_RIGHT_SUPER];
>>>>>>> 6096232c0915328fcc92793c1dda5d2ffdbe916e
		return false;
	}
	
	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
<<<<<<< HEAD
		m_io.KeysDown[e.GetKeyCode()] = false;
=======
		m_io.KeysDown[e.GetKeycode()] = false;
>>>>>>> 6096232c0915328fcc92793c1dda5d2ffdbe916e
		return false;
	}

	bool WLD::ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		int32_t keycode = e.GetKeyCode();

		if (keycode > 0 && keycode < 0x10000)
			m_io.AddInputCharacter((uint8_t)keycode);

		return false;
	}
	
	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		m_io.DisplaySize = ImVec2(e.GetWidth(), e.GetHight());
		m_io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.GetWidth(), e.GetHight());

		return false;
	}
}
