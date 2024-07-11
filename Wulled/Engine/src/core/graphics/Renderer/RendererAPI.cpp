#include "WLDPCH.h"
#include "RendererAPI.h"


namespace WLD
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::None;

	RendererAPI::API RendererAPI::s_NextAPI = RendererAPI::API::OpenGL;
//	RendererAPI::API RendererAPI::s_NextAPI = RendererAPI::API::Vulkan;
}