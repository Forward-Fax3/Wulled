#include "wldpch.h"
#include "GraphicsContext.h"
#include "Renderer.h"
#include "WLDMem.h"

#include "OpenGL/Context.h"
#include "DX12/Context.h"
#include "WLDVk/Context.h"


namespace WLD::Graphics
{
	GraphicsContext* GraphicsContext::createGraphicsContext(HWND* window, const WindowProps& props)
	{
		switch (Renderer::Renderer::GetAPI())
		{
			case Renderer::RendererAPI::API::None:      WLD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case Renderer::RendererAPI::API::OpenGL:    return CreateMemory(OpenGL::OpenGLContext, window);
			case Renderer::RendererAPI::API::DirectX12: return CreateMemory(dx12::DX12Context, window);
//			case Renderer::RendererAPI::API::Vulkan:    return CreateMemory(Vulkan::VulkanContext, window, props);
			default: WLD_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
		}
	}
}