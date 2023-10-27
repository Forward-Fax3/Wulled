#pragma once
#include "Engine/src/Core/pch/wldpch.h"

#include "Engine/src/Core/Layers/LayerStack.h"

#include "Engine/src/Core/window.h"

#include "Engine/src/Core/Events/Event.h"
#include "Engine/src/Core/Events/ApplicationEvent.h"



namespace WLD
{
	class WLD_API Application
	{
	public:
		Application(bool* run);
		virtual ~Application();

		void run();

		inline bool* GetRunPtrs() { return m_run; }

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline static Application* GetPtr() { return s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool* m_run;
		LayerStack m_LayerStack;

		static Application* s_Instance;
	};

	Application* CreateApplication(bool* run);
}
