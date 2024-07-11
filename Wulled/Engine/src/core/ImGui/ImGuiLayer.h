#pragma once
#include "Engine/src/Core/EngineCore.h"

#include "imgui.h"

#include "Engine/src/Core/Layers/Layer.h"

#include "Engine/src/Core/Events/Event.h"
#include "Engine/src/Core/Events/KeyEvent.h"
#include "Engine/src/Core/Events/MouseEvent.h"
#include "Engine/src/Core/Events/ApplicationEvent.h"

#include "Engine/src/Core/Graphics/GraphicsContext.h"


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
	};
}