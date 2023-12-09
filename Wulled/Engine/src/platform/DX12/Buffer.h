#pragma once
#include "Engine/src/core/EngineCore.h"
#include "Engine/src/core/graphics/Renderer/Buffer.h"


namespace WLD::Graphics::dx12
{
	class WLD_API DX12VertexBuffer : public Renderer::Buffers::VertexBuffer
	{
	public:
		DX12VertexBuffer(float* vertices, uint32_t size);
		virtual ~DX12VertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		
		virtual void SetLayout(const Renderer::Buffers::BufferLayout& layout) override { m_Layout = layout; }
		virtual const Renderer::Buffers::BufferLayout& GetLayout() const override { return m_Layout; }

	private:
		uint32_t m_RendererID;
		Renderer::Buffers::BufferLayout m_Layout;
	};

class WLD_API DX12IndexBuffer : public Renderer::Buffers::IndexBuffer
	{
	public:
		DX12IndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~DX12IndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const override { return m_Count; }

	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}