#pragma once
#include "Engine/src/core/EngineCore.h"
#include "Engine/src/core/graphics/Renderer/Shader.h"


namespace WLD
{
	class WLD_API DX12Shader : public Shader
	{
	public:
		DX12Shader(const std::vector<InputShader>& shaders);
		~DX12Shader();

		virtual void SetInt(const std::string& name, int value) override {}
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override {}
		virtual void SetFloat(const std::string& name, float value) override {}
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) override {}
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override {}
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override {}
		virtual void SetMat2(const std::string& name, const glm::mat2& value) override {}
		virtual void SetMat3(const std::string& name, const glm::mat3& value) override {}
		virtual void SetMat4(const std::string& name, const glm::mat4& value) override {}

		virtual void SetPushConst(const std::string& UBName, const std::vector<PushConstOpaqueObj>& layout, const void* data) override {};
//		virtual void SetUniformBuffer(const std::string& UBName, const std::string* uniformNames, size_t numOfNames, const void* data) {}

		virtual void Bind() const override;
		virtual void Unbind() const override;
	};
}