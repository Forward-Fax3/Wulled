#pragma once
#include "Engine/src/core/graphics/renderer/Buffer.h"


namespace WLD::Graphics::Renderer
{
	class WLD_API VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<Buffers::VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<Buffers::IndexBuffer>& vertexBuffer) = 0;

		virtual const std::vector<Ref<Buffers::VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<Buffers::IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};
}