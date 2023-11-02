#include "wldpch.h"
#include "VertexArray.h"
#include "Renderer.h"

#include "OpenGLVertexArray.h"

namespace WLD
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: WLD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
//		case RendererAPI::API::DirectX11: return new DX11VertexArray();
//		case RendererAPI::API::DirectX12: return new DX12VertexArray();

		default: WLD_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
		}
	}
}