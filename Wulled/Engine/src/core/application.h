#pragma once
#include "Engine/src/core/EngineCore.h"
#include "Engine/src/core/layers/LayerStack.h"

#include "Engine/src/core/Window.h"

#include "Engine/src/core/Events/Event.h"
#include "Engine/src/core/Events/ApplicationEvent.h"

#include "Engine/src/core/ImGui/ImGuiLayer.h"
#include "Engine/src/core/Time/WLDTime.h"
#include "Engine/src/core/Threads/WLDThread.h"

#include "Engine/src/core/graphics/Renderer/Shader.h"
#include "Engine/src/core/graphics/Renderer/Buffer.h"
#include "Engine/src/core/graphics/Renderer/VertexArray.h"


namespace WLD
{
	class WLD_API Application
	{
	public:
		Application(bool* run);
		virtual ~Application();

		void Run();

		inline bool* GetRunPtrs() { return m_Run; }

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		void PushAsyncFunction(std::function<void(void*)> function, void* data);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() const { return *m_Window; }
		inline bool* GetRun() const { return m_Run; } // 0 - Run, 1 - restart, 2 - APISet, 3 - APIReset

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

		bool* m_Run; // 0 - Run, 1 - restart, 2 - APISet, 3 - APIReset

		static Application* s_Instance;
	};

	Application* CreateApplication(bool* run, int argc, char** argv);
}