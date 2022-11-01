#pragma once
#include "Engine/src/Core/pch/wldpch.h"
#include "Engine/src/Core/EngineCore.h"

#include "imgui.h"
#include "Engine/src/platform/openGL/ImGuiOpenGLRenderer.h"

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

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& e) override;

	private:
		float m_Time;
		ImGuiIO& io;

		ImGuiIO& init();

		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
	};
}