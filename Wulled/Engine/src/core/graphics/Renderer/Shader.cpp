#include "wldpch.h"
#include "log.h"
#include "EngineCore.h"

#include "Renderer.h"

#include "Shader.h"
#include "OpenGL/Shader.h"
#include "DX12/Shader.h"


namespace WLD::Graphics::Renderer
{
	Shader* Shader::Create(const std::string_view& vertexSrc, const std::string_view& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: WLD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:    return new OpenGL::OpenGLShader(vertexSrc, fragmentSrc);
//		case RendererAPI::API::DirectX11: return new DX11Shader(vertexSrc, fragmentSrc);
		case RendererAPI::API::DirectX12: return new dx12::DX12Shader(vertexSrc, fragmentSrc);

		default: WLD_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
		}
	}
}