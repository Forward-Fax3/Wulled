#include "wldpch.h"
#include "RenderCommand.h"
#include "WLDMem.h"

#include "OpenGLRendererAPI.h"
#include "DX12RendererAPI.h"
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
//			case RendererAPI::API::DirectX11: s_RendererAPI = new DX11RendererAPI(); return;
			case RendererAPI::API::DirectX12: s_RendererAPI = CreateMemory(DX12RendererAPI); return;
//			case RendererAPI::API::Vulkan: WLD_CORE_ASSERT(false, "RendererAPI::Vulkan is Currently being implemented!"); return;
			case RendererAPI::API::Vulkan: s_RendererAPI = CreateMemory(VkRendererAPI); return;
		}
	}

	void RenderCommand::DeleteRendererAPI()
	{
		s_RendererAPI = DestroyMemory(s_RendererAPI);
	}
}