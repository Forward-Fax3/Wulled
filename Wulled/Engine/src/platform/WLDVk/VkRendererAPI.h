#pragma once
#include "RendererAPI.h"

#include <vulkan/vulkan.h>


namespace WLD
{
	class WLD_API VulkanRendererAPI : public RendererAPI
	{
	public:
		virtual ~VulkanRendererAPI() override;

		virtual void Init() override;
		virtual void Clear() override;

		virtual void BeginScene() override;
		virtual void EndScene() override;

		virtual void DrawIndexed(const WLD::Ref<VertexArray> vertexArray) override;

	private:
		VkCommandPool m_CommandPool;
		VkCommandBuffer m_CommnadBuffer;

		VkClearValue m_ClearValue{};
	};
}
