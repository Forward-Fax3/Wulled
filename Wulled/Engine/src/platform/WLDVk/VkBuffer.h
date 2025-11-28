#pragma once
#include "Buffer.h"
#include "vulkan/vulkan.h"


namespace WLD
{
	class VulkanVertexBuffer : public VertexBuffer
	{
	public:
		VulkanVertexBuffer(float* vertices, uint32_t size);
		~VulkanVertexBuffer() override;

		virtual void Bind() const override;
		void Bind(VkCommandBuffer commandBuffer);
		virtual void Unbind() const override;

		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		virtual const BufferLayout& GetLayout() const override { return m_Layout;  }

	private:
		BufferLayout m_Layout{};

		VkBuffer m_VertexBuffer = nullptr;
		VkDeviceMemory m_DeviceMemory = nullptr;
	};

	class VulkanIndexBuffer : public IndexBuffer
	{
	public:
		VulkanIndexBuffer(uint32_t* indices, uint32_t count);
		~VulkanIndexBuffer() override;

		virtual void Bind() const override;
		void Bind(VkCommandBuffer commandBuffer);
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const override { return m_Count; };

	private:
		uint32_t m_Count;

		VkBuffer m_IndexBuffer = nullptr;
		VkDeviceMemory m_DeviceMemory = nullptr;
	};
}