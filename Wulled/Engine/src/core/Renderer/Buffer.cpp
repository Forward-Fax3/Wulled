#include "wldpch.h"
#include "log.h"
#include "EngineCore.h"

#include "Renderer.h"
#include "Buffer.h"
#include "OpenGLBuffer.h"


namespace WLD
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: WLD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
//		case RendererAPI::API::DirectX11: return new DX11VertexBuffer(vertices, size);
//		case RendererAPI::API::DirectX12: return new DX12VertexBuffer(vertices, size);

		default: WLD_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
		}
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: WLD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, size);
//		case RendererAPI::API::DirectX11: return new DX11IndexBuffer(indices, size);
//		case RendererAPI::API::DirectX12: return new DX12IndexBuffer(indices, size);

		default: WLD_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
		}
	}
}