#include "wldpch.h"
#include "GraphicsContext.h"
#include "Application.h"
#include "Renderer.h"

#include "OpenGLContext.h"
#include "DX12Context.h"


namespace WLD::Graphics::Renderer
{
	GraphicsContext* GraphicsContext::createGraphicsContext(HWND* window)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    WLD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return new OpenGL::OpenGLContext(window);
			case RendererAPI::API::DX12:    return new dx12::DX12Context(window);
			default: WLD_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
		}
	}
}