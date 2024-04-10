#pragma once
#include "Engine/src/Core/Events/Event.h"


namespace WLD
{
	class WLD_API Layer
	{
	public:
		Layer(std::string name);
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiDraw() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string GetName() const { return m_DebugName; }

#ifdef IN_LAYERSTACK_CPP
		inline bool GetDeletionInLayerStack() const { return DeletionInLayerStack; }
#endif

	protected:
		bool DeletionInLayerStack = true;

	private:
		std::string m_DebugName;
	};
}