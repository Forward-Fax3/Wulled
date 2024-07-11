#include "WLDPCH.h"
#include "Texture.h"
#include "Renderer.h"
#include "OpenGLTexture.h"


namespace WLD
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: WLD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateMemory(OpenGLTexture2D, path);
		default: WLD_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
		}
	}
}
