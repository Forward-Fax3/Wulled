#include "wldpch.h"

#include "LayerStack.h"
#include "Window.h"
#include "WinWindow.h"
#include "ApplicationEvent.h"
#include "application.h"

#include <chrono>


namespace WLD
{
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application(bool* run)
		: m_run(run), m_LayerStack(new LayerStack)
	{
		WLD_ASSERT(!s_Instance, "Application already Exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create(WindowProps(L"SandBox", 1920, 1080)));
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent)); 

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		s_Instance = nullptr;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack->PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack->PushOverlay(overlay);
		overlay->OnAttach(); 
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack->end(); it != m_LayerStack->begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.GetHandled())
				break;
		}
	}

	void Application::run()
	{
		MSG msg;

		while (m_run[0])
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT) break;
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			for (Layer* layer : *m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : *m_LayerStack)
				layer->OnImGuiDraw();
			m_ImGuiLayer->end();

			m_Window->OnUpdate();
			calcDeltaTime();
		}
	}
	
	void Application::calcDeltaTime()
	{
		const auto currentTime = std::chrono::steady_clock::now();
		static auto lastTime = currentTime;
		m_deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastTime).count() / 1000000.0f;
		lastTime = currentTime;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_run[0] = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		m_Window->onWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}
}
