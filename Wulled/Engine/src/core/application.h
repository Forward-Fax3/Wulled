#pragma once
#include "Engine/src/core/EngineCore.h"
#include "Engine/src/Core/Layers/LayerStack.h"

#include "Engine/src/Core/window.h"

#include "Engine/src/Core/Events/Event.h"
#include "Engine/src/Core/Events/ApplicationEvent.h"

#include "Engine/src/Core/ImGui/ImGuiLayer.h"
#include "Engine/src/core/Time/WLDTime.h"

#include "Engine/src/core/graphics/Renderer/Shader.h"
#include "Engine/src/core/graphics/Renderer/Buffer.h"
#include "Engine/src/core/graphics/Renderer/VertexArray.h"

#include <thread>


namespace WLD
{
	class WLD_API Application
	{
	public:
		Application(bool* run);
		virtual ~Application();

		void run();

		inline bool* GetRunPtrs() { return m_run; }

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline static Application* GetPtr() { return s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
		inline bool* GetRun() { return m_run; } // 0 - run, 1 - restart, 2 - APISet, 3 - APIReset

	private:
		void OnEvent(Event& e);
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		Ref<Window> m_Window;
		Scope<LayerStack> m_LayerStack;

		ImGuiLayer* m_ImGuiLayer;
		Time* m_Time;

		bool* m_run; // 0 - run, 1 - restart, 2 - APISet, 3 - APIReset

		static Application* s_Instance;
	};

	Application* CreateApplication(bool* run, int argc, char** argv);
}
