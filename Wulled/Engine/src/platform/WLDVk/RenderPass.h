#pragma once
#include "EngineCore.h"
#include "vulkan/vulkan.hpp"


namespace WLD
{
	class RenderPass
	{
	public:
		RenderPass();
		~RenderPass();

		VkRenderPass& GetRenderPass() { return m_RenderPass; }

	private:
		VkRenderPass m_RenderPass = nullptr;
	};
}