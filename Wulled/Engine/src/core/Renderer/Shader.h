#pragma once
#include "Engine/src/core/EngineCore.h"
#include "glm/glm.hpp"


namespace WLD::Graphics::Renderer
{
	class WLD_API Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		// Set uniforms
		virtual void SetUniformMat4fv(std::string_view name, glm::mat4 MVP) = 0;

		static Shader* Create(const std::string_view& vertexSrc, const std::string_view& fragmentSrc);
	};
}
