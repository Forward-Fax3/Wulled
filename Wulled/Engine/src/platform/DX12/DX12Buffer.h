#pragma once
#include "Engine/src/core/EngineCore.h"
#include "Engine/src/core/graphics/Renderer/Buffer.h"


namespace WLD
{
	class WLD_API DX12VertexBuffer : public VertexBuffer
	{
	public:
		DX12VertexBuffer(float* vertices, uint32_t size);
		virtual ~DX12VertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		virtual const BufferLayout& GetLayout() const override { return m_Layout; }

	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

class WLD_API DX12IndexBuffer : public IndexBuffer
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