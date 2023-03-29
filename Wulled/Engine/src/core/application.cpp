// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com


#include "wldpch.h"

#include "LayerStack.h"
#include "Window.h"
#include "WinWindow.h"
#include "application.h"
#include "ApplicationEvent.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"


namespace WLD
{
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application(bool* run)
		: m_run(run)
	{		
		WLD_ASSERT(!s_Instance, "Application already Exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		
		uint32_t id;
		glGenBuffers(1, &id);
	}

	Application::~Application()
	{
		s_Instance = nullptr;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach(); 
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
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
			glClearColor(1.0f, 105.0f / 255.0f, 180.0f/255.0f, 1.0f);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
			glClear(GL_COLOR_BUFFER_BIT);
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_run[0] = false;
		return true;
	}
}
