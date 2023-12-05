#pragma once
#include "Engine/src/core/graphics/renderer/VertexArray.h"


namespace WLD::Graphics::OpenGL
{
	class WLD_API OpenGLVertexArray : public Renderer::VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<Renderer::Buffers::VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<Renderer::Buffers::IndexBuffer>& vertexBuffer) override;

		virtual const std::vector<std::shared_ptr<Renderer::Buffers::VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; };
		virtual const std::shared_ptr<Renderer::Buffers::IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; };

	private:
		uint32_t m_RendererID;
		std::vector<std::shared_ptr<Renderer::Buffers::VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<Renderer::Buffers::IndexBuffer> m_IndexBuffer;
	};
}