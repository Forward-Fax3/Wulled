#include "wldpch.h"
#include "VertexArray.h"
#include "Renderer.h"

#include "OpenGLVertexArray.h"

namespace WLD::Graphics::Renderer
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: WLD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGL::OpenGLVertexArray();
//		case RendererAPI::API::DirectX11: return new dx11::DX11VertexArray();
//		case RendererAPI::API::DirectX12: return new dx12::DX12VertexArray();

		default: WLD_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
		}
	}
}