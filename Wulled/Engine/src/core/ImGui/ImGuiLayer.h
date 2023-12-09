#pragma once
#include "Engine/src/Core/EngineCore.h"

#include "imgui.h"

#include "Engine/src/Core/layers/Layer.h"

#include "Engine/src/Core/Events/Event.h"
#include "Engine/src/Core/Events/KeyEvent.h"
#include "Engine/src/Core/Events/MouseEvent.h"
#include "Engine/src/Core/Events/ApplicationEvent.h"


namespace WLD
{
	class WLD_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() override;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiDraw() override;

		void Begin();
		void end();

	private:
		void OpenGLInit();
		void DX12Init();
		void OpenGLShutdown();
		void DX12Shutdown();

		void APIInit();
		void APIShutdown();
		
		void DX12RenderDrawData();
		void OpenGLRenderDrawData();

		bool OnWindowResize(WindowResizeEvent& e);

	protected:
		ImGuiIO& m_io;

	private:
		ImGuiIO& init();

		void (*ImGui_ImplX_NewFrame)(void);
		std::function<void()> ImGui_ImplX_RenderDrawData;
	};
}