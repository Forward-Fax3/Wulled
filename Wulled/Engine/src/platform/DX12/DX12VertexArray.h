#pragma once
#include "Engine/src/core/EngineCore.h"
#include "Engine/src/core/WLDMem.h"
#include "Engine/src/core/graphics/Renderer/VertexArray.h"


namespace WLD
{
	class WLD_API DX12VertexArray : public VertexArray
	{
	public:
		DX12VertexArray();
		~DX12VertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const WLD::Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const WLD::Ref<IndexBuffer>& vertexBuffer) override;

		virtual const std::vector<WLD::Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; };
		virtual const WLD::Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; };

	private:
		uint32_t m_RendererID;
		std::vector<WLD::Ref<VertexBuffer>> m_VertexBuffers;
		WLD::Ref<IndexBuffer> m_IndexBuffer;
	};
}