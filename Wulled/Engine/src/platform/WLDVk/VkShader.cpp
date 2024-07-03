#include "wldpch.h"
#include "application.h"
#include "VkShader.h"
#include "VkErrors.h"
#include "VkContext.h"
#include "WLDFileStream.h"

#include "shaderc/shaderc.hpp"
#include "spirv_cross/spirv_glsl.hpp"

#include <string>
#include <fstream>


namespace WLD
{
	VulkanShader::VulkanShader(const std::vector<InputShader>& shaders)
	{
		SetUpRenderPass();
		std::vector<std::pair<VkShaderStageFlagBits, std::vector<uint32_t>>> shaderSources;
		shaderSources.reserve(shaders.size());
		for (const auto& shader : shaders)
		{
			std::string filePath = "assets/shaders/" + shader.source;
			std::vector<uint32_t> SPIR_V;
			if (!FileStream::ReadFile(filePath + ".spv", SPIR_V))
			{
				std::string VkGLSL;
				WLD_CORE_ASSERT(FileStream::ReadFile(filePath, VkGLSL), "Failed to read shader file!");
				SPIR_V = CompileToVkSPIRV(VkGLSL, filePath, ShadercShaderTypeFromWLDShaderType(shader.type));
			}
			shaderSources.emplace_back(VkShaderTypeFromWLDShaderType(shader.type), SPIR_V);
		}
		Compile(shaderSources);
	}

	VulkanShader::~VulkanShader()
	{
	}

	void VulkanShader::Bind() const
	{
	}

	void VulkanShader::Unbind() const
	{
	}

	void VulkanShader::SetInt(const std::string& name, int value)
	{
	}

	void VulkanShader::SetIntArray(const std::string& name, int* values, uint32_t count)
	{
	}

	void VulkanShader::SetFloat(const std::string& name, float value)
	{
	}

	void VulkanShader::SetFloat2(const std::string& name, const glm::vec2& value)
	{
	}

	void VulkanShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
	}

	void VulkanShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
	}

	void VulkanShader::SetMat2(const std::string& name, const glm::mat2& value)
	{
	}

	void VulkanShader::SetMat3(const std::string& name, const glm::mat3& value)
	{
	}

	void VulkanShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
	}

	void VulkanShader::SetPushConst(const std::string& UBName, const std::vector< PushConstOpaqueObj>& layout, const void* data)
	{
	}

	void VulkanShader::SetUpRenderPass()
	{
		VulkanContext& vkContext = dynamic_cast<VulkanContext&>(Application::Get().GetWindow().GetGraphicsContext());
		VkAttachmentDescription colorAttachment{};
		colorAttachment.format = vkContext.GetSwapChain().GetImageFormat();
		colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
		colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		VkAttachmentReference colorAttachmentRef{};
		colorAttachmentRef.attachment = 0;
		colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkSubpassDescription subpass{};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &colorAttachmentRef;

		VkSubpassDependency dependency{};
		dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		dependency.dstSubpass = 0;
		dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.srcAccessMask = 0;
		dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

		VkRenderPassCreateInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassInfo.attachmentCount = 1;
		renderPassInfo.pAttachments = &colorAttachment;
		renderPassInfo.subpassCount = 1;
		renderPassInfo.pSubpasses = &subpass;
		renderPassInfo.dependencyCount = 1;
		renderPassInfo.pDependencies = &dependency;

		WLD_VkCheckError(vkCreateRenderPass(vkContext.GetDevice(), &renderPassInfo, nullptr, &m_RenderPass));
	}

	void VulkanShader::Compile(const std::vector<std::pair<VkShaderStageFlagBits, std::vector<uint32_t>>>& shaderSources)
	{
		VulkanContext& vkContext = dynamic_cast<VulkanContext&>(Application::Get().GetWindow().GetGraphicsContext());
		std::vector<VkPipelineShaderStageCreateInfo> shaderStages;
		shaderStages.reserve(shaderSources.size());
		spirv_cross::CompilerGLSL* GLSLCompiler = nullptr;
		spirv_cross::ShaderResources* resources = nullptr;
		for (const auto& [type, source] : shaderSources)  
		{
			VkShaderModuleCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
			createInfo.codeSize = source.size() * sizeof(uint32_t);
			createInfo.pCode = source.data();

			VkShaderModule shaderModule;
			WLD_VkCheckError(vkCreateShaderModule(vkContext.GetDevice(), &createInfo, nullptr, &shaderModule));
			// TODO: allow for multiple and other entry points
			shaderStages.emplace_back(VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO, nullptr, 0, type, shaderModule, "main", nullptr); // using emplace_back contruction to avoid copying the VkPipelineShaderStageCreateInfo

			if (type != VK_SHADER_STAGE_VERTEX_BIT)
				continue;
			
			GLSLCompiler = CreateMemory(spirv_cross::CompilerGLSL, source);
			resources = CreateMemory(spirv_cross::ShaderResources, GLSLCompiler->get_shader_resources());
		}

		if (!GLSLCompiler)
		{
			LOG_CORE_FATAL("No Vertex Shader provided!");
			return;
		}

		std::vector<VkDynamicState> dynamicStates =
		{
			VK_DYNAMIC_STATE_VIEWPORT,
			VK_DYNAMIC_STATE_SCISSOR
		};

		VkPipelineDynamicStateCreateInfo dynamicStateCreateInfo{};
		dynamicStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamicStateCreateInfo.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
		dynamicStateCreateInfo.pDynamicStates = dynamicStates.data();

		VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
		vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexInputInfo.vertexBindingDescriptionCount = 0;

		std::vector<VkVertexInputAttributeDescription> attributeDescriptions;
		attributeDescriptions.reserve(resources->stage_inputs.size());

		for (const auto& stageInput : resources->stage_inputs)
		{
			const auto& type = GLSLCompiler->get_type(stageInput.type_id);
			const auto& name = stageInput.name;
			LOG_CORE_INFO("Input: {0}, Type: {1}", name, (int32_t)type.basetype);
			attributeDescriptions.emplace_back
			(
				GLSLCompiler->get_decoration(stageInput.id, spv::DecorationLocation),
				0,
				VkFormatFromSPIRType(type),
				0
			);
		}

		for (auto& shader : shaderStages)
			vkDestroyShaderModule(vkContext.GetDevice(), shader.module, nullptr);

		GLSLCompiler = DestroyMemory(GLSLCompiler);
		resources = DestroyMemory(resources);
	}

	VkShaderStageFlagBits VulkanShader::VkShaderTypeFromWLDShaderType(WLD_ShaderType type) const
	{
		switch (type)
		{
		case WLD_ShaderType::Vertex: return VK_SHADER_STAGE_VERTEX_BIT;
		case WLD_ShaderType::Fragment: return VK_SHADER_STAGE_FRAGMENT_BIT;
		default: return VkShaderStageFlagBits();
		}
	}

	shaderc_shader_kind VulkanShader::ShadercShaderTypeFromWLDShaderType(WLD_ShaderType type) const
	{
		switch (type)
		{
		case WLD_ShaderType::Vertex: return shaderc_shader_kind::shaderc_glsl_vertex_shader;
		case WLD_ShaderType::Fragment: return shaderc_shader_kind::shaderc_glsl_fragment_shader;
		}
		LOG_CORE_FATAL("unkown shader type");
		return (shaderc_shader_kind)-1;
	}

	VkFormat VulkanShader::VkFormatFromSPIRType(const spirv_cross::SPIRType& type) const
	{
		switch (type.basetype)
		{
		case spirv_cross::SPIRType::Float:
		{
			switch (type.vecsize)
			{
			case 1: return VK_FORMAT_R32_SFLOAT;
			case 2: return VK_FORMAT_R32G32_SFLOAT;
			case 3: return VK_FORMAT_R32G32B32_SFLOAT;
			case 4: return VK_FORMAT_R32G32B32A32_SFLOAT;
			}
		}
		case spirv_cross::SPIRType::Double:
		{
			switch (type.vecsize)
			{
			case 1: return VK_FORMAT_R64_SFLOAT;
			case 2: return VK_FORMAT_R64G64_SFLOAT;
			case 3: return VK_FORMAT_R64G64B64_SFLOAT;
			case 4: return VK_FORMAT_R64G64B64A64_SFLOAT;
			}
		}
		case spirv_cross::SPIRType::Int:
		{
			switch (type.vecsize)
			{
			case 1: return VK_FORMAT_R32_SINT;
			case 2: return VK_FORMAT_R32G32_SINT;
			case 3: return VK_FORMAT_R32G32B32_SINT;
			case 4: return VK_FORMAT_R32G32B32A32_SINT;
			}
		}
		case spirv_cross::SPIRType::UInt:
		{
			switch (type.vecsize)
			{
			case 1: return VK_FORMAT_R32_UINT;
			case 2: return VK_FORMAT_R32G32_UINT;
			case 3: return VK_FORMAT_R32G32B32_UINT;
			case 4: return VK_FORMAT_R32G32B32A32_UINT;
			}
		}
		default: return VK_FORMAT_UNDEFINED;
		}
	}
}
