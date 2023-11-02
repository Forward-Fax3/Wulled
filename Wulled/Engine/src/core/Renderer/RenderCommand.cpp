#include "wldpch.h"
#include "RenderCommand.h"
#include "OpenGLRendererAPI.h"


namespace WLD
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
//	RendererAPI* RenderCommand::s_RendererAPI = new DX11RendererAPI();
//	RendererAPI* RenderCommand::s_RendererAPI = new DX12RendererAPI();
}