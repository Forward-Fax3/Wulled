#pragma once
#include <string>
#include "Engine/src/core/EngineCore.h"
#include "Engine/src/core/graphics/Renderer/Shader.h"
#include "glm/glm.hpp"


namespace WLD::Graphics::OpenGL
{
	class WLD_API OpenGLShader : public Renderer::Shader
	{
	public:
		OpenGLShader(const std::string_view& vertexSrc, const std::string_view& fragmentSrc);
		~OpenGLShader();

		void Bind() const;
		void Unbind() const;

		virtual void SetUniformMat4fv(std::string_view name, glm::mat4 MVP) override;

	private:
		uint32_t m_RendererID;
	};
}