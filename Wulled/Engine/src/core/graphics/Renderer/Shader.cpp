#include "wldpch.h"
#include "EngineCore.h"
#include "WLDMem.h"

#include "Renderer.h"

#include "Shader.h"
#include "OpenGL/Shader.h"
#include "DX12/Shader.h"


namespace WLD::Graphics::Renderer
{
	Shader* Shader::Create(const std::string_view& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: WLD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:    return CreateMemory(OpenGL::OpenGLShader, filepath);
//		case RendererAPI::API::DirectX11: return new DX11Shader(vertexSrc, fragmentSrc);
		case RendererAPI::API::DirectX12: return CreateMemory(dx12::DX12Shader, filepath);

		default: WLD_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
		}
	}

	Shader* Shader::Create(const std::string_view& vertexSrc, const std::string_view& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: WLD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:    return CreateMemory(OpenGL::OpenGLShader, vertexSrc, fragmentSrc);
//		case RendererAPI::API::DirectX11: return new DX11Shader(vertexSrc, fragmentSrc);
		case RendererAPI::API::DirectX12: return CreateMemory(dx12::DX12Shader, vertexSrc, fragmentSrc);

		default: WLD_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
		}
	}
}