#include "wldpch.h"

#include "LayerStack.h"
#include "Window.h"
#include "Windows/Window.h"
#include "ApplicationEvent.h"
#include "application.h"
#include "Renderer.h"
#include "RenderCommand.h"
#include "WLDMem.h"


namespace WLD
{
	Application* Application::s_Instance = nullptr;

	Application::Application(bool* run)
		: m_run(run)
	{
		WLD_CORE_ASSERT(!s_Instance, "Application already Exists!");
		s_Instance = this;
		m_LayerStack = CreateScope(LayerStack);
		m_Time = CreateMemory(Time);
		PushLayer(m_Time);

		m_Window = Window::Create(WindowProps(L"SandBox", 1920, 1080));
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		Graphics::Renderer::Renderer::Init();

		m_ImGuiLayer = CreateMemory(ImGuiLayer);
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		s_Instance = nullptr;
		DestroyScope(m_LayerStack);
		Graphics::Renderer::Renderer::Shutdown();
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

	void WLD::Application::PopLayer(Layer* layer)
	{
		m_LayerStack->PopLayer(layer);
		layer->OnDetach();
	}

	void WLD::Application::PopOverlay(Layer* overlay)
	{
		m_LayerStack->PopOverlay(overlay);
		overlay->OnDetach();
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
			m_LayerStack->OnUpdate();
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
