#pragma once
#include "Engine/src/core/EngineCore.h"
#include "Engine/src/core/graphics/Renderer/Shader.h"


namespace WLD::Graphics::dx12
{
	class WLD_API DX12Shader : public Renderer::Shader
	{
	public:
		DX12Shader(const std::string_view& filepath);
		DX12Shader(const std::string_view& vertexSrc, const std::string_view& fragmentSrc);
		~DX12Shader();

		virtual void Bind() const override;
		virtual void Unbind() const override;
	};
}