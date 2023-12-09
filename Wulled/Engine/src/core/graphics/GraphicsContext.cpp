#include "wldpch.h"
#include "GraphicsContext.h"
#include "application.h"
#include "Renderer.h"

#include "OpenGL/Context.h"
#include "DX12/Context.h"


namespace WLD::Graphics
{
	GraphicsContext* GraphicsContext::createGraphicsContext(HWND* window)
	{
		switch (Renderer::Renderer::GetAPI())
		{
			case Renderer::RendererAPI::API::None:    WLD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case Renderer::RendererAPI::API::OpenGL:  return new OpenGL::OpenGLContext(window);
			case Renderer::RendererAPI::API::DirectX12:    return new dx12::DX12Context(window);
			default: WLD_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
		}
	}
}