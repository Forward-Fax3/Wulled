#include "wldpch.h"
#include "GraphicsContext.h"
#include "Renderer.h"
#include "WLDMem.h"

#include "OpenGLContext.h"
#include "DX12Context.h"
#include "VKContext.h"


namespace WLD
{
	GraphicsContext* GraphicsContext::createGraphicsContext(WindowProps& props)
	{
		switch (Renderer::Renderer::GetAPI())
		{
		case RendererAPI::API::None:      LOG_CORE_FATAL("RendererAPI::None is currently not supported!"); break;
		case RendererAPI::API::OpenGL:    return CreateMemory(OpenGLContext, props);
		case RendererAPI::API::DirectX12: return CreateMemory(DX12Context, props);
//		case RendererAPI::API::DirectX12: LOG_CORE_FATAL("DirectX12 is currently not supported");
		case RendererAPI::API::Vulkan:    return CreateMemory(VulkanContext, props);
		default: WLD_CORE_ASSERT(false, "Unknown RendererAPI!");
		}
		return nullptr;
	}
}