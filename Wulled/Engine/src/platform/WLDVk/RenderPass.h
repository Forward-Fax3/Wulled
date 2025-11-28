#pragma once
#include "EngineCore.h"
#include "vulkan/vulkan.h"



namespace WLD
{
	class VulkanContext;

	class RenderPass
	{
	public:
		RenderPass(const VulkanContext& context);
		~RenderPass();

		void BeginRenderPass(VkCommandBuffer commandBuffer, const VkClearValue& clearValue);
		void EndRenderPass();

		VkRenderPass GetRenderPass() const { return m_RenderPass; }

	private:
		VkRenderPass m_RenderPass = nullptr;
	};
}

#ifndef WLD_VKCONTEXT_H
#include "VkContext.h"
#endif