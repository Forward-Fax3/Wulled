#include "wldpch.h"
#include "Texture.h"
#include "Renderer.h"
#include "OpenGL/Texture.h"


namespace WLD::Graphics::Renderer
{
	Ref<Texture2D> Texture2D::Create(const std::string_view& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: WLD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateMemory(OpenGL::OpenGLTexture2D, path);
//		case RendererAPI::API::DirectX12: return CreateMemory(dx12::DX12Texture2D, path);
		default: WLD_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
		}
	}
}
