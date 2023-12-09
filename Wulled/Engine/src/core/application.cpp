#include "wldpch.h"

#include "LayerStack.h"
#include "Window.h"
#include "Windows/Window.h"
#include "ApplicationEvent.h"
#include "application.h"
#include "RenderCommand.h"


namespace WLD
{
	Application* Application::s_Instance = nullptr;

	Application::Application(bool* run)
		: m_run(run), m_LayerStack(new LayerStack)
	{
		WLD_CORE_ASSERT(!s_Instance, "Application already Exists!");
		s_Instance = this;
		m_Time = new Time();
		PushLayer(m_Time);

		m_Window = std::unique_ptr<Window>(Window::Create(WindowProps(L"SandBox", 1920, 1080)));
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		Graphics::Renderer::RenderCommand::CreateRendererAPI();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		s_Instance = nullptr;
		Graphics::Renderer::RenderCommand::DeleteRendererAPI();
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
		while (m_run[0])
		{
			for (Layer* layer : *m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : *m_LayerStack)
				layer->OnImGuiDraw();
			m_ImGuiLayer->end();

			m_Window->OnUpdate();
		}
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
