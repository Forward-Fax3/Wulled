#pragma once
#include <string>
#include <queue>

#include "Engine/src/core/EngineCore.h"
#include "Engine/src/core/graphics/Renderer/Shader.h"

#include "glm/glm.hpp"
#include "GL/glew.h"
#include "shaderc/shaderc.hpp"


namespace WLD
{
	class WLD_API OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::vector<InputShader>& shaders);
		~OpenGLShader();

		void Bind() const override;
		void Unbind() const override;

		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;
		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void SetMat2(const std::string& name, const glm::mat2& value) override;
		virtual void SetMat3(const std::string& name, const glm::mat3& value) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) override;

		virtual void SetPushConst(const std::string& UBName, const std::vector<PushConstOpaqueObj>& layout, const void* data) override;
//		virtual void SetUniformBuffer(const std::string& UBName, const std::string* uniformNames, size_t numOfNames, const void* data);

//		void SetUniformInt(std::string name, const int value);
//		
//		void SetUniformFloat(std::string name, const float value);
//		void SetUniformFloat2(std::string name, const glm::vec2& values);
//		void SetUniformFloat3(std::string name, const glm::vec3& values);
//		void SetUniformFloat4(std::string name, const glm::vec4& values);
//
//
//		void SetUniformMat2fv(std::string name, const glm::mat2& matrix);
//		void SetUniformMat3fv(std::string name, const glm::mat3& matrix);
//		void SetUniformMat4fv(std::string name, const glm::mat4& matrix);

	private:
		enum class ShaderSourceType : uint8_t
		{
			None = 0,
			source,
			OpenGL,
			Vulkan
		};

		struct ShaderInfo
		{
			WLD_ShaderType Type = WLD_ShaderType::None;
			std::vector<uint32_t> source;
		};

	private:
		void Compile(const std::vector<ShaderInfo>& shaderSources);
		bool GetOGLSPIRVfromVkSPIRVOrSource(const std::string& filePath, WLD_ShaderType Type, int32_t& pushConstsLocations, std::vector<uint32_t>& result);
		std::vector<uint32_t> CrossCompile(const std::vector<uint32_t>& shaderSource, const std::string& filePath, int32_t& pushConstsLocations, shaderc_shader_kind shaderType);
		void Reflect(const std::vector<uint32_t>& shaderSource);

		GLenum GetOGLShaderTypeFromWLDShaderType(WLD_ShaderType type) const;
		shaderc_shader_kind GetShadercShaderKindFromWLDShaderType(WLD_ShaderType type) const;

	private:
		uint32_t m_RendererID = NULL;
		std::queue<uint32_t> m_ShaderIDs;

		std::unordered_map<std::string, uint32_t> m_PushConstantsLocations;
	};
}