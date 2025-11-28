#include "vulkan/vulkan.h"

#include "VkErrors.h"

#include "VkBuffer.h"
#include "VkMemoryAllocator.h"
#include "VkContext.h"

#include "application.h"


namespace WLD
{
	// Vertex Buffer
	VulkanVertexBuffer::VulkanVertexBuffer(float* vertices, uint32_t size)
	{
		const VulkanContext& vkContext = dynamic_cast<const VulkanContext&>(Application::Get().GetWindow().GetGraphicsContext());

		VkBufferCreateInfo bufferInfo{};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = size;
		bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		WLD_VkCheckError(vkCreateBuffer(vkContext.GetDevice(), &bufferInfo, nullptr, &m_VertexBuffer));

		m_DeviceMemory = VulkanMemoryAllocator::GetAllocator().AllocateMemory(m_VertexBuffer);
		VulkanVertexBuffer::Bind();

		void* data = nullptr;
		WLD_VkCheckError(vkMapMemory(vkContext.GetDevice(), m_DeviceMemory, 0, size, 0, &data));
		memcpy(data, vertices, size);

//		VulkanVertexBuffer::Unbind();
	}

	VulkanVertexBuffer::~VulkanVertexBuffer()
	{
		const VulkanContext& vkContext = dynamic_cast<const VulkanContext&>(Application::Get().GetWindow().GetGraphicsContext());

		vkUnmapMemory(vkContext.GetDevice(), m_DeviceMemory);
		vkDestroyBuffer(vkContext.GetDevice(), m_VertexBuffer, nullptr);
		VulkanMemoryAllocator::GetAllocator().DeallocateMemory(m_DeviceMemory);
	}

	void VulkanVertexBuffer::Bind() const
	{
		const VulkanContext& vkContext = dynamic_cast<const VulkanContext&>(Application::Get().GetWindow().GetGraphicsContext());
		WLD_VkCheckError(vkBindBufferMemory(vkContext.GetDevice(), m_VertexBuffer, m_DeviceMemory, 0));
	}

	void VulkanVertexBuffer::Bind(VkCommandBuffer commandBuffer)
	{
		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, &m_VertexBuffer, offsets);
	}

	void VulkanVertexBuffer::Unbind() const
	{
		const VulkanContext& vkContext = dynamic_cast<const VulkanContext&>(Application::Get().GetWindow().GetGraphicsContext());
		WLD_VkCheckError(vkBindBufferMemory(vkContext.GetDevice(), m_VertexBuffer, nullptr, 0));
	}

	// Index Buffer
	VulkanIndexBuffer::VulkanIndexBuffer(uint32_t* indices, uint32_t count)
		: m_Count(count)
	{
		const VulkanContext& vkContext = dynamic_cast<const VulkanContext&>(Application::Get().GetWindow().GetGraphicsContext());

		VkBufferCreateInfo bufferInfo{};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = m_Count * sizeof(uint32_t);
		bufferInfo.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		WLD_VkCheckError(vkCreateBuffer(vkContext.GetDevice(), &bufferInfo, nullptr, &m_IndexBuffer));

		m_DeviceMemory = VulkanMemoryAllocator::GetAllocator().AllocateMemory(m_IndexBuffer);
		VulkanIndexBuffer::Bind();

		void* data = nullptr;
		WLD_VkCheckError(vkMapMemory(vkContext.GetDevice(), m_DeviceMemory, 0, m_Count * sizeof(uint32_t), 0, &data));
		memcpy(data, indices, m_Count * sizeof(uint32_t));

//		VulkanIndexBuffer::Unbind();
	}

	VulkanIndexBuffer::~VulkanIndexBuffer()
	{
		const VulkanContext& vkContext = dynamic_cast<const VulkanContext&>(Application::Get().GetWindow().GetGraphicsContext());
		
		vkUnmapMemory(vkContext.GetDevice(), m_DeviceMemory);
		vkDestroyBuffer(vkContext.GetDevice(), m_IndexBuffer, nullptr);
		VulkanMemoryAllocator::GetAllocator().DeallocateMemory(m_DeviceMemory);
	}

	void VulkanIndexBuffer::Bind() const
	{
		const VulkanContext& vkContext = dynamic_cast<const VulkanContext&>(Application::Get().GetWindow().GetGraphicsContext());
		WLD_VkCheckError(vkBindBufferMemory(vkContext.GetDevice(), m_IndexBuffer, m_DeviceMemory, 0));
	}

	void VulkanIndexBuffer::Bind(VkCommandBuffer commandBuffer)
	{
		vkCmdBindIndexBuffer(commandBuffer, m_IndexBuffer, 0, VK_INDEX_TYPE_UINT32);
	}

	void VulkanIndexBuffer::Unbind() const
	{
		const VulkanContext& vkContext = dynamic_cast<const VulkanContext&>(Application::Get().GetWindow().GetGraphicsContext());
		WLD_VkCheckError(vkBindBufferMemory(vkContext.GetDevice(), m_IndexBuffer, nullptr, 0));
	}
}