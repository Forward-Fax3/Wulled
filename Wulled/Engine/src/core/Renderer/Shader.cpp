#include "wldpch.h"
#include "log.h"
#include "EngineCore.h"

#include "Renderer.h"

#include "Shader.h"
#include "OpenGLShader.h"


namespace WLD
{
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: WLD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
//		case RendererAPI::API::DirectX11: return new DX11Shader(vertexSrc, fragmentSrc);
//		case RendererAPI::API::DirectX12: return new DX12Shader(vertexSrc, fragmentSrc);

		default: WLD_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
		}
	}
}