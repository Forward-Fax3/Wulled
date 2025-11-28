#include "wldpch.h"
#include "RenderCommand.h"
#include "WLDMem.h"

#include "OpenGLRendererAPI.h"
#include "VkRendererAPI.h"


namespace WLD
{
	RendererAPI* RenderCommand::s_RendererAPI = nullptr;

	void RenderCommand::CreateRendererAPI()
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None: WLD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return;
			case RendererAPI::API::OpenGL: s_RendererAPI = CreateMemory(OpenGLRendererAPI); return;
			case RendererAPI::API::Vulkan: s_RendererAPI = CreateMemory(VulkanRendererAPI); return;
		}
	}

	void RenderCommand::DeleteRendererAPI()
	{
		DestroyMemory(s_RendererAPI);
	}
}