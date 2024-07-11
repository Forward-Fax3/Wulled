#include "WLDPCH.h"
#include "WLDMem.h"

#define IN_LAYERSTACK_CPP
#include "LayerStack.h"


namespace WLD
{
	// LayerStackQueue
	LayerStackQueue::LayerStackQueue()
		: m_LayerInsertIndex(0)
	{
	}

	LayerStackQueue::~LayerStackQueue()
	{
		for (auto& [layer, type] : m_Layers)
		{
			LOG_CORE_TRACE("Deleting layer {0}", layer->GetName());
			DestroyMemory(layer);
		}
		clear();
	}

	void LayerStackQueue::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer, LayerStackQueueType::layerPush);
		m_LayerInsertIndex++;
	}

	void LayerStackQueue::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay, LayerStackQueueType::overlayPush);
	}

	void LayerStackQueue::PopLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer, LayerStackQueueType::layerPop);
		m_LayerInsertIndex++;
	}

	void LayerStackQueue::PopOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay, LayerStackQueueType::overlayPop);
	}

	void LayerStackQueue::clear()
	{
		m_Layers.clear();
		m_LayerInsertIndex = 0;
	}

	// LayerStack
	LayerStack::LayerStack()
		: m_LayerInsertIndex(0) {}

	LayerStack::~LayerStack()
	{
		for (auto& layer : m_Layers)
		{
			LOG_CORE_TRACE("Deleting layer {0}", layer->GetName());
			layer->OnDetach();
			DestroyMemory(layer);
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_LayerStackQueue.PushLayer(layer);
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_LayerStackQueue.PushOverlay(overlay);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		m_LayerStackQueue.PopLayer(layer);
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		m_LayerStackQueue.PopOverlay(overlay);
	}

	void LayerStack::OnUpdate()
	{
		for (auto& [layer, type] : m_LayerStackQueue)
		{
			switch (type)
			{
			case LayerStackQueueType::layerPush:
				_PushLayer(layer);
				continue;
			case LayerStackQueueType::layerPop:
				_PopLayer(layer);
				continue;
			case LayerStackQueueType::overlayPush:
				_PushOverlay(layer);
				continue;
			case LayerStackQueueType::overlayPop:
				_PopOverlay(layer);
				continue;
			}
		}
		m_LayerStackQueue.clear();
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
		DestroyMemory(layer);
		if (layer)
		{
			std::string name = layer->GetName();
			try
			{
				delete layer;
				LOG_CORE_WARNING("Layer {0} was created thought Wulled memory creation but has been deleted", name);
			}
			catch (const std::exception& e)
			{
				LOG_CORE_ERROR("Layer {0} was created thought Wulled memory creation but has not been deleted", name);
			}
		}
	}

	void LayerStack::_PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
			m_Layers.erase(it);
		DestroyMemory(overlay);
		if (overlay)
		{
			std::string name = overlay->GetName();
			try
			{
				delete overlay;
				LOG_CORE_WARNING("Overlay {0} was created thought Wulled memory creation but has been deleted", name);
			}
			catch (const std::exception& e)
			{
				LOG_CORE_ERROR("Overlay {0} was created thought Wulled memory creation but has not been deleted", name);
			}
		}
	}
}