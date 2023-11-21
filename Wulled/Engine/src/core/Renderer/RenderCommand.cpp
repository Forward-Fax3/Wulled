#include "wldpch.h"
#include "RenderCommand.h"
#include "OpenGLRendererAPI.h"


namespace WLD::Graphics::Renderer
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGL::OpenGLRendererAPI();
//	RendererAPI* RenderCommand::s_RendererAPI = new DX11RendererAPI();
//	RendererAPI* RenderCommand::s_RendererAPI = new DX12RendererAPI();
}