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

		virtual void AddVertexBuffer(const std::shared_ptr<Buffers::VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<Buffers::IndexBuffer>& vertexBuffer) = 0;

		virtual const std::vector<std::shared_ptr<Buffers::VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const std::shared_ptr<Buffers::IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};
}