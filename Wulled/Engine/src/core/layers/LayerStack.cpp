#include "wldpch.h"
#include "WLDMem.h"

#define IN_LAYERSTACK_CPP
#include "LayerStack.h"


namespace WLD
{
	LayerStackQueue::LayerStackQueue()
		: m_LayerInsertIndex(0)
	{
	}

	LayerStackQueue::~LayerStackQueue()
	{
		for (auto& layer : m_Layers)
		{
			WLD_CORE_TRACE("Deleting layer {0}", layer.first->GetName());
			layer.first = DestroyMemory(layer.first);
		}
	}

	void LayerStackQueue::PushLayer(Layer* layer)
	{
		std::pair<Layer*, LayerStackQueueType> tempPair = { layer, LayerStackQueueType::layerPush };
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, tempPair);
		m_LayerInsertIndex++;
	}

	void LayerStackQueue::PushOverlay(Layer* overlay)
	{
		std::pair<Layer*, LayerStackQueueType> tempPair = { overlay, LayerStackQueueType::overlayPush };
		m_Layers.emplace_back(tempPair);
	}

	void LayerStackQueue::PopLayer(Layer* layer)
	{
		std::pair<Layer*, LayerStackQueueType> tempPair = { layer, LayerStackQueueType::layerPop };
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, tempPair);
		m_LayerInsertIndex++;
	}

	void LayerStackQueue::PopOverlay(Layer* overlay)
	{
		std::pair<Layer*, LayerStackQueueType> tempPair = { overlay, LayerStackQueueType::overlayPop };
		m_Layers.emplace_back(tempPair);
	}

	void LayerStackQueue::clear()
	{
		m_Layers.clear();
		m_LayerInsertIndex = 0;
	}

	LayerStack::LayerStack()
		: m_LayerInsertIndex(0)
	{
		m_LayerStackQueue = CreateScope(LayerStackQueue);
	}

	LayerStack::~LayerStack()
	{
		for (auto layer : m_Layers)
		{
			WLD_CORE_TRACE("Deleting layer {0}", layer->GetName());
			layer = DestroyMemory(layer);
		}
		DestroyScope(m_LayerStackQueue);
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_LayerStackQueue->PushLayer(layer);
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_LayerStackQueue->PushOverlay(overlay);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		m_LayerStackQueue->PopLayer(layer);
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		m_LayerStackQueue->PopOverlay(overlay);
	}

	void LayerStack::OnUpdate()
	{
		for (auto& layer : *m_LayerStackQueue)
		{
			switch (layer.second)
			{
			case LayerStackQueueType::layerPush:
				_PushLayer(layer.first);
				continue;
			case LayerStackQueueType::layerPop:
				_PopLayer(layer.first);
				continue;
			case LayerStackQueueType::overlayPush:
				_PushOverlay(layer.first);
				continue;
			case LayerStackQueueType::overlayPop:
				_PopOverlay(layer.first);
				continue;
			}
		}
		m_LayerStackQueue->clear();
	}

	void LayerStack::_PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}

	void LayerStack::_PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}

	void LayerStack::_PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
		layer = DestroyMemory(layer);
		if (layer)
		{
			WLD_CORE_WARNING("Layer {0} was created thought Wulled memory creation but has been deleted", layer->GetName());
			delete layer;
		}
	}

	void LayerStack::_PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
			m_Layers.erase(it);
		overlay = DestroyMemory(overlay);
		if (overlay)
		{
			WLD_CORE_WARNING("Overlay {0} was created thought Wulled memory creation but has been deleted", overlay->GetName());
			delete overlay;
		}
	}
}