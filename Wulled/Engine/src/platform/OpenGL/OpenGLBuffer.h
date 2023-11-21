#pragma once
#include "Engine/src/core/renderer/Buffer.h"

#include <cstdint>

namespace WLD::Graphics::OpenGL
{
	class WLD_API OpenGLVertexBuffer : public Renderer::Buffers::VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetLayout(const Renderer::Buffers::BufferLayout& layout) override { m_Layout = layout; }
		virtual const Renderer::Buffers::BufferLayout& GetLayout() const override { return m_Layout; }

	private:
		uint32_t m_RendererID;
		Renderer::Buffers::BufferLayout m_Layout;
	};

	class WLD_API OpenGLIndexBuffer : public Renderer::Buffers::IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const override { return m_Count; }

	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}