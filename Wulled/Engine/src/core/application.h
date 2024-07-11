#pragma once
#include "Engine/src/Core/EngineCore.h"
#include "Engine/src/Core/Layers/LayerStack.h"

#include "Engine/src/Core/Window.h"

#include "Engine/src/Core/Events/Event.h"
#include "Engine/src/Core/Events/ApplicationEvent.h"

#include "Engine/src/Core/ImGui/ImGuiLayer.h"
#include "Engine/src/Core/Time/WLDTime.h"
#include "Engine/src/Core/Threads/WLDThread.h"

#include "Engine/src/Core/Graphics/Renderer/Shader.h"
#include "Engine/src/Core/Graphics/Renderer/Buffer.h"
#include "Engine/src/Core/Graphics/Renderer/VertexArray.h"


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

		void PushAsyncFunction(std::function<void(void*)> function, void* data);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
		inline bool* GetRun() { return m_run; } // 0 - run, 1 - restart, 2 - APISet, 3 - APIReset

	// Functions
	private:
		void OnEvent(Event& e);
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	// Data
	private:
		Window* m_Window;
		WindowProps m_Props;
		
		Scope<LayerStack> m_LayerStack;
		Scope<WLDThreads> m_Threads;

		ImGuiLayer* m_ImGuiLayer = nullptr;
		Time* m_Time = nullptr;

		bool* m_run; // 0 - run, 1 - restart, 2 - APISet, 3 - APIReset

		static Application* s_Instance;
	};

	Application* CreateApplication(bool* run, int argc, char** argv);
}