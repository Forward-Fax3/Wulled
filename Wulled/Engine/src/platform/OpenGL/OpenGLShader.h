#pragma once
#include <string>
#include "Engine/src/core/EngineCore.h"
#include "Engine/src/core/Renderer/Shader.h"


namespace WLD
{
	class WLD_API OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader();

		void Bind() const;
		void Unbind() const;

	private:
		uint32_t m_RendererID;
	};
}