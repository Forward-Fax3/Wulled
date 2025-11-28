#pragma once
#include "Engine/src/core/EngineCore.h"

#include "imgui.h"

#include "Engine/src/core/layers/Layer.h"

#include "Engine/src/core/Events/Event.h"
#include "Engine/src/core/Events/KeyEvent.h"
#include "Engine/src/core/Events/MouseEvent.h"
#include "Engine/src/core/Events/ApplicationEvent.h"

#include "Engine/src/core/graphics/GraphicsContext.h"


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
		void End();

	private:
		bool OnWindowResize(WindowResizeEvent& e);
	};
}