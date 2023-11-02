#pragma once
#include "Engine/src/core/EngineCore.h"


namespace WLD
{
	class WLD_API Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};
}
