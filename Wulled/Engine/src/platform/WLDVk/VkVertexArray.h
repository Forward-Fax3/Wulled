#pragma once
#include "VertexArray.h"

#include "vulkan/vulkan.h"


namespace WLD
{
	class VulkanVertexArray : public VertexArray
	{
	public:
		VulkanVertexArray();
		virtual ~VulkanVertexArray() override;

		virtual void Bind() const override;
		void Bind(VkCommandBuffer commandBuffer) const;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer> vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer> vertexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>> GetVertexBuffers() const override { return m_VertexBuffers; };
		virtual const Ref<IndexBuffer> GetIndexBuffer() const override { return m_IndexBuffer; };

	private:
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}
