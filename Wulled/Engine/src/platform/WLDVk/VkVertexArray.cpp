#include "VkVertexArray.h"

#include "VkBuffer.h"


namespace WLD
{

	VulkanVertexArray::VulkanVertexArray()
	{

	}

	VulkanVertexArray::~VulkanVertexArray()
	{

	}

	void VulkanVertexArray::Bind() const
	{
		m_VertexBuffers[0]->Bind();
	}

	void VulkanVertexArray::Bind(VkCommandBuffer commandBuffer) const
	{
		std::vector<VulkanVertexBuffer*> vkVertexBuffers;
		vkVertexBuffers.reserve(m_VertexBuffers.size());
		for (auto& vertexBuffer : m_VertexBuffers)
			vkVertexBuffers.emplace_back(dynamic_cast<VulkanVertexBuffer*>(vertexBuffer.get()));

		VulkanIndexBuffer* vkIndexBuffer = dynamic_cast<VulkanIndexBuffer*>(m_IndexBuffer.get());

		vkVertexBuffers[0]->Bind(commandBuffer);
		vkIndexBuffer->Bind(commandBuffer);
	}

	void VulkanVertexArray::Unbind() const
	{

	}

	void VulkanVertexArray::AddVertexBuffer(const Ref<VertexBuffer> vertexBuffer)
	{
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void VulkanVertexArray::SetIndexBuffer(const Ref<IndexBuffer> indexBuffer)
	{
		m_IndexBuffer = indexBuffer;
	}
}