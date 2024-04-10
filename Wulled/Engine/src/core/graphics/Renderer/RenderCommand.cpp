#include "wldpch.h"
#include "RenderCommand.h"
#include "WLDMem.h"

#include "OpenGL/RendererAPI.h"
#include "DX12/RendererAPI.h"


namespace WLD::Graphics::Renderer
{
	RendererAPI* RenderCommand::s_RendererAPI = nullptr;

	void RenderCommand::CreateRendererAPI()
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None: WLD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return;
			case RendererAPI::API::OpenGL: s_RendererAPI = CreateMemory(OpenGL::OpenGLRendererAPI); return;
//			case RendererAPI::API::DirectX11: s_RendererAPI = new DX11RendererAPI(); return;
			case RendererAPI::API::DirectX12: s_RendererAPI = CreateMemory(dx12::DX12RendererAPI); return;
			case RendererAPI::API::Vulkan: WLD_CORE_ASSERT(false, "RendererAPI::Vulkan is Currently being implemented!"); return;
//			case RendererAPI::API::Vulkan: s_RendererAPI = CreateMemory(Vk::VulkanRendererAPI); return;
		}
	}

	void RenderCommand::DeleteRendererAPI()
	{
		s_RendererAPI = DestroyMemory(s_RendererAPI);
	}
}