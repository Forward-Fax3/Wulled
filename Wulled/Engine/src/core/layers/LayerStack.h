#pragma once
#include "Engine/src/core/EngineCore.h"

#include "Engine/src/core/layers/Layer.h"


namespace WLD
{
	enum class LayerStackQueueType : uint8_t
	{
		None,
		layerPush,
		layerPop,
		overlayPush,
		overlayPop
	};

	class WLD_API LayerStack;

	class WLD_API LayerStackQueue
	{
	private: // helper struct
		struct LayerData
		{
			inline LayerData(Layer* layer, LayerStackQueueType type)
				: layer(layer), type(type) {}

			~LayerData() = default;

			Layer* layer = nullptr;
			LayerStackQueueType type = LayerStackQueueType::None;
		};

	private:
		LayerStackQueue();
		~LayerStackQueue();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		inline std::vector<LayerData>::iterator begin() { return m_Layers.begin(); }
		inline std::vector<LayerData>::iterator end() { return m_Layers.end(); }

		void clear();

	private:
		std::vector<LayerData> m_Layers;
		uint64_t m_LayerInsertIndex;

		friend class LayerStack;
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
		void PrivateFunction_PushLayer(Layer* layer);
		void PrivateFunction_PushOverlay(Layer* overlay);
		void PrivateFunction_PopLayer(Layer* layer);
		void PrivateFunction_PopOverlay(Layer* overlay);

	private:
		std::vector<Layer*> m_Layers;
		LayerStackQueue m_LayerStackQueue;
		uint64_t m_LayerInsertIndex;
	};
}
