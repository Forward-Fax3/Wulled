#include "wldpch.h"
#include "RendererAPI.h"


namespace WLD::Graphics::Renderer
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::None;

	RendererAPI::API RendererAPI::s_NextAPI = RendererAPI::API::OpenGL;
//	RendererAPI::API RendererAPI::s_NextAPI = RendererAPI::API::DirectX11;
//	RendererAPI::API RendererAPI::s_NextAPI = RendererAPI::API::DirectX12;

}