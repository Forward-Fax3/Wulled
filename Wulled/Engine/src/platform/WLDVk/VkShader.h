#pragma once
#include "Engine/src/core/graphics/Renderer/Shader.h"

#include <shaderc/shaderc.hpp>

#include <vulkan/vulkan.h>
#include "spirv_cross/spirv_glsl.hpp"


namespace WLD
{
	class VulkanShader : public Shader
	{
	public:
		VulkanShader(const std::vector<InputShader>& shaders);
		virtual ~VulkanShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

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

	private: // Helper Struts
		struct VertexInputAttributeData
		{
			VkFormat format = VK_FORMAT_UNDEFINED;
			uint32_t size = NULL;
		};

	private: // Helper Functions
		void Compile(const std::vector<std::pair<VkShaderStageFlagBits, std::vector<uint32_t>>>& shaderSources);

		VkShaderStageFlagBits VkShaderTypeFromWLDShaderType(WLD_ShaderType type) const;
		shaderc_shader_kind ShadercShaderTypeFromWLDShaderType(WLD_ShaderType type) const;
		VertexInputAttributeData VertexInputAttributeDataFromSPIRType(const spirv_cross::SPIRType& type) const;

	private: // Data
		VkPipelineLayout m_PipelineLayout;
		VkPipeline m_GraphicsPipeline;
		std::vector<VkDescriptorSetLayout> m_DescriptorSetLayouts;
	};
}
