#include "wldpch.h"
#include "RenderCommand.h"
#include "OpenGL/RendererAPI.h"
#include "DX12/RendererAPI.h"


namespace WLD::Graphics::Renderer
{
	void RenderCommand::CreateRendererAPI()
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None: WLD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return;
			case RendererAPI::API::OpenGL: s_RendererAPI = new OpenGL::OpenGLRendererAPI(); return;
//			case RendererAPI::API::DirectX11: s_RendererAPI = new DX11RendererAPI(); return;
			case RendererAPI::API::DirectX12: s_RendererAPI = new dx12::DX12RendererAPI(); return;
		}
	}

}