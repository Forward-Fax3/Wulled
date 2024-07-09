#pragma once
#include "Engine/Src/Core/EngineCore.h"

#include "imgui.h"

#include "Engine/Src/Core/layers/Layer.h"

#include "Engine/Src/Core/Events/Event.h"
#include "Engine/Src/Core/Events/KeyEvent.h"
#include "Engine/Src/Core/Events/MouseEvent.h"
#include "Engine/Src/Core/Events/ApplicationEvent.h"

#include "Engine/Src/Core/Graphics/GraphicsContext.h"


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
		bool OnWindowResize(WindowResizeEvent& e);

		ImGuiIO& init();

	private:
		ImGuiIO& m_io;
		GraphicsContext& m_Context;
	};
}