#pragma once
#include "Engine/src/Core/EngineCore.h"

#include "Engine/src/Core/Layers/Layer.h"


namespace WLD
{
	enum class LayerStackQueueType : uint8_t
	{
		layerPush,
		layerPop,
		overlayPush,
		overlayPop
	};

	class WLD_API LayerStackQueue
	{
	public:
		LayerStackQueue();
		~LayerStackQueue();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		inline std::vector<std::pair<Layer*, LayerStackQueueType>>::iterator begin() { return m_Layers.begin(); }
		inline std::vector<std::pair<Layer*, LayerStackQueueType>>::iterator end() { return m_Layers.end(); }

		void clear();

	private:
		std::vector<std::pair<Layer*, LayerStackQueueType>> m_Layers;
		uint64_t m_LayerInsertIndex;
	};

	class WLD_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		void OnUpdate();

		inline std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		inline std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		void _PushLayer(Layer* layer);
		void _PushOverlay(Layer* overlay);
		void _PopLayer(Layer* layer);
		void _PopOverlay(Layer* overlay);

	private:
		std::vector<Layer*> m_Layers;
		Scope<LayerStackQueue> m_LayerStackQueue;
		uint64_t m_LayerInsertIndex;
	};
}