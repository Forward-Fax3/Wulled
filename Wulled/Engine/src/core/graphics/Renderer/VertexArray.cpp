#include "wldpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "WLDMem.h"

#include "OpenGLVertexArray.h"
#include "VkVertexArray.h"

namespace WLD
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: WLD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateMemory(OpenGLVertexArray);
		case RendererAPI::API::Vulkan: return CreateMemory(VulkanVertexArray);

		default: WLD_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
		}
	}
}