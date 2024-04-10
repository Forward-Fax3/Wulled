#pragma once
#include <string>
#include "Engine/src/core/EngineCore.h"
#include "Engine/src/core/graphics/Renderer/Shader.h"
#include "glm/glm.hpp"
#include "glatter/glatter.h"


namespace WLD::Graphics::OpenGL
{
	class WLD_API OpenGLShader : public Renderer::Shader
	{
	public:
		OpenGLShader(const std::string_view& filepath);
		OpenGLShader(const std::string_view& vertexSrc, const std::string_view& fragmentSrc);
		~OpenGLShader();

		void Bind() const;
		void Unbind() const;

		void SetUniformInt(std::string_view name, const int value);
		
		void SetUniformFloat(std::string_view name, const float value);
		void SetUniformFloat2(std::string_view name, const glm::vec2& values);
		void SetUniformFloat3(std::string_view name, const glm::vec3& values);
		void SetUniformFloat4(std::string_view name, const glm::vec4& values);


		void SetUniformMat2fv(std::string_view name, const glm::mat2& matrix);
		void SetUniformMat3fv(std::string_view name, const glm::mat3& matrix);
		void SetUniformMat4fv(std::string_view name, const glm::mat4& matrix);

	private:
		std::string ReadFile(const std::string_view& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string_view& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

	private:
		uint32_t m_RendererID;
	};
}