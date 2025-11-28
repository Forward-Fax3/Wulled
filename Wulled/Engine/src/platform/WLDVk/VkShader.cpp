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
		const VulkanContext& vkContext = dynamic_cast<const VulkanContext&>(Application::Get().GetWindow().GetGraphicsContext());
		vkDestroyPipeline(vkContext.GetDevice(), m_GraphicsPipeline, nullptr);
		vkDestroyPipelineLayout(vkContext.GetDevice(), m_PipelineLayout, nullptr);
	}

	void VulkanShader::Bind() const
	{
		const VulkanContext& vkContext = dynamic_cast<const VulkanContext&>(Application::Get().GetWindow().GetGraphicsContext());
		vkCmdBindPipeline(vkContext.GetCommandBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, m_GraphicsPipeline);
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

	void VulkanShader::Compile(const std::vector<std::pair<VkShaderStageFlagBits, std::vector<uint32_t>>>& shaderSources)
	{
		Window& window = Application::Get().GetWindow();
		const VulkanContext& vkContext = dynamic_cast<const VulkanContext&>(window.GetGraphicsContext());
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
#if (__cplusplus == 202002L)
			shaderStages.emplace_back(VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO, nullptr, 0, type, shaderModule, "main", nullptr); // using emplace_back construction to avoid copying the VkPipelineShaderStageCreateInfo
#else
			VkPipelineShaderStageCreateInfo info = {};
			info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			info.pNext = nullptr;
			info.flags = 0;
			info.stage = type;
			info.module = shaderModule;
			info.pName = "main";
			info.pSpecializationInfo = nullptr;
			shaderStages.emplace_back(info);
#endif

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

		constexpr uint32_t numberOfDynamicStates = 2;
		VkDynamicState dynamicStates[numberOfDynamicStates] =
		{
			VK_DYNAMIC_STATE_VIEWPORT,
			VK_DYNAMIC_STATE_SCISSOR
		};

		VkPipelineDynamicStateCreateInfo dynamicStateCreateInfo{};
		dynamicStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamicStateCreateInfo.dynamicStateCount = numberOfDynamicStates;
		dynamicStateCreateInfo.pDynamicStates = dynamicStates;

		std::vector<VkVertexInputAttributeDescription> attributeDescriptions;
		attributeDescriptions.reserve(resources->stage_inputs.size());
		uint32_t vertexInputAttributeDataOffset = 0;

		for (const auto& stageInput : resources->stage_inputs)
		{
			const auto& type = GLSLCompiler->get_type(stageInput.type_id);
			const auto& name = stageInput.name;
			const auto& location = GLSLCompiler->get_decoration(stageInput.id, spv::DecorationLocation);
			const auto& binding = GLSLCompiler->get_decoration(stageInput.id, spv::DecorationBinding);
			const auto [format, size] = VertexInputAttributeDataFromSPIRType(type);
			LOG_CORE_INFO("name: {0}, Location: {1}, binding {4}, Format: {2}, Size: {3}", name, location, static_cast<uint32_t>(format), size, binding);
#if (__cplusplus == 202002L)
			attributeDescriptions.emplace_back
			(
				location,
				binding,
				format,
				vertexInputAttributeDataOffset
			);
#else
			VkVertexInputAttributeDescription attributeDescription{};
			attributeDescription.location = location;
			attributeDescription.binding = binding;
			attributeDescription.format = format;
			attributeDescription.offset = vertexInputAttributeDataOffset;
			attributeDescriptions.emplace_back(attributeDescription);
#endif
			vertexInputAttributeDataOffset += size;
		}

		VkVertexInputBindingDescription bindingDescription{};
		bindingDescription.binding = 0;
		bindingDescription.stride = vertexInputAttributeDataOffset;
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
		vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexInputInfo.vertexBindingDescriptionCount = 1;
		vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
		vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
		vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

		VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
		inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		inputAssembly.primitiveRestartEnable = VK_FALSE;

		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = (float)window.GetWidth();
		viewport.height = (float)window.GetHeight();
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		VkRect2D scissor{};
		scissor.offset = { 0, 0 };
		scissor.extent = { window.GetWidth(), window.GetHeight() };
		
		VkPipelineViewportStateCreateInfo viewportState{};
		viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportState.viewportCount = 1;
		viewportState.pViewports = &viewport;
		viewportState.scissorCount = 1;
		viewportState.pScissors = &scissor;

		VkPipelineRasterizationStateCreateInfo rasterizer{};
		rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizer.depthClampEnable = VK_FALSE;
		rasterizer.rasterizerDiscardEnable = VK_FALSE;
		rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
		rasterizer.lineWidth = 1.0f;
		rasterizer.cullMode = VK_CULL_MODE_FRONT_BIT;
		rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
		rasterizer.depthBiasEnable = VK_FALSE;

		VkPipelineMultisampleStateCreateInfo multisampling{};
		multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampling.sampleShadingEnable = VK_FALSE;
		multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

		VkPipelineDepthStencilStateCreateInfo depthStencil{};
		depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		depthStencil.depthTestEnable = VK_TRUE;
		depthStencil.depthWriteEnable = VK_TRUE;
		depthStencil.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
		depthStencil.depthBoundsTestEnable = VK_FALSE;
		depthStencil.stencilTestEnable = VK_FALSE;

		VkPipelineColorBlendAttachmentState colorBlendAttachment{};
		colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		colorBlendAttachment.blendEnable = VK_TRUE;
		colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
		colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
		colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
		colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
		colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
		colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

		VkPipelineColorBlendStateCreateInfo colorBlending{};
		colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		colorBlending.logicOpEnable = VK_FALSE;
		colorBlending.logicOp = VK_LOGIC_OP_COPY;
		colorBlending.attachmentCount = 1;
		colorBlending.pAttachments = &colorBlendAttachment;

		std::map<uint32_t, std::vector<VkDescriptorSetLayoutBinding>> orderedDescriptorSetBindingsLayouts;
		VkShaderStageFlagBits stages[2]{}; // for now until i figure out a dynamic way to handle this
		stages[0] = VK_SHADER_STAGE_VERTEX_BIT;
		stages[1] = (VkShaderStageFlagBits)(VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT);
		size_t i = 0;

		for (const auto& UBO : resources->uniform_buffers)
		{
			const auto& name = UBO.name;
			const auto& set = GLSLCompiler->get_decoration(UBO.id, spv::DecorationDescriptorSet);
			const auto& binding = GLSLCompiler->get_decoration(UBO.id, spv::DecorationBinding);

			VkDescriptorSetLayoutBinding layoutBinding{};
			layoutBinding.binding = binding;
			layoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
			layoutBinding.descriptorCount = 1;
			layoutBinding.stageFlags = stages[i];
			layoutBinding.pImmutableSamplers = nullptr;

			i++;

			orderedDescriptorSetBindingsLayouts[set].push_back(layoutBinding);
			LOG_CORE_TRACE("UBO: {0}, set: {1}, Binding: {2}", name, set, binding);
		}

		std::vector<VkDescriptorSetLayout> descriptorSetBindingLayouts;
		descriptorSetBindingLayouts.reserve(orderedDescriptorSetBindingsLayouts.size());

		for (const auto& [set, setBindings] : orderedDescriptorSetBindingsLayouts)
		{
			VkDescriptorSetLayoutCreateInfo layoutInfo{};
			layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
			layoutInfo.bindingCount = static_cast<uint32_t>(setBindings.size());
			layoutInfo.pBindings = setBindings.data();

			VkDescriptorSetLayout descriptorSetLayout = nullptr;
			WLD_VkCheckError(vkCreateDescriptorSetLayout(vkContext.GetDevice(), &layoutInfo, nullptr, &descriptorSetLayout));
			descriptorSetBindingLayouts.emplace_back(descriptorSetLayout);
		}

		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetBindingLayouts.size());
		pipelineLayoutInfo.pSetLayouts = descriptorSetBindingLayouts.data();
		pipelineLayoutInfo.pushConstantRangeCount = 0;

		WLD_VkCheckError(vkCreatePipelineLayout(vkContext.GetDevice(), &pipelineLayoutInfo, nullptr, &m_PipelineLayout));

		VkGraphicsPipelineCreateInfo pipelineInfo{};
		pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineInfo.stageCount = static_cast<uint32_t>(shaderStages.size());
		pipelineInfo.pStages = shaderStages.data();
		pipelineInfo.pVertexInputState = &vertexInputInfo;
		pipelineInfo.pInputAssemblyState = &inputAssembly;
		pipelineInfo.pViewportState = &viewportState;
		pipelineInfo.pRasterizationState = &rasterizer;
		pipelineInfo.pMultisampleState = &multisampling;
		pipelineInfo.pDepthStencilState = &depthStencil;
		pipelineInfo.pColorBlendState = &colorBlending;
		pipelineInfo.pDynamicState = &dynamicStateCreateInfo;
		pipelineInfo.layout = m_PipelineLayout;
		pipelineInfo.renderPass = vkContext.GetRenderPass();
		pipelineInfo.subpass = 0;
		pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

		WLD_VkCheckError(vkCreateGraphicsPipelines(vkContext.GetDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_GraphicsPipeline));

		for (auto& shader : shaderStages)
			vkDestroyShaderModule(vkContext.GetDevice(), shader.module, nullptr);

		DestroyMemory(GLSLCompiler);
		DestroyMemory(resources);
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
		case WLD_ShaderType::None: LOG_CORE_ERROR("No Shader Type Provided!"); return (shaderc_shader_kind)-1;
		case WLD_ShaderType::Vertex: return shaderc_shader_kind::shaderc_glsl_vertex_shader;
		case WLD_ShaderType::Fragment: return shaderc_shader_kind::shaderc_glsl_fragment_shader;
		}
		LOG_CORE_FATAL("unkown shader type");
		return (shaderc_shader_kind)-1;
	}

	VulkanShader::VertexInputAttributeData VulkanShader::VertexInputAttributeDataFromSPIRType(const spirv_cross::SPIRType& type) const
	{
		VertexInputAttributeData data{};
		switch (type.basetype) // TODO: add more types
		{
		case spirv_cross::SPIRType::Unknown:
		case spirv_cross::SPIRType::Void:
		{
			data.format = VK_FORMAT_UNDEFINED;
			data.size = 0;
			break;
		}
		case spirv_cross::SPIRType::Boolean:
		{
			switch (type.vecsize)
			{
			case 1: data.format = VK_FORMAT_R8_UINT; break;
			case 2: data.format = VK_FORMAT_R8G8_UINT; break;
			case 3: data.format = VK_FORMAT_R8G8B8_UINT; break;
			case 4: data.format = VK_FORMAT_R8G8B8A8_UINT; break;
			default: data.format = VK_FORMAT_UNDEFINED;
			}
			data.size = sizeof(bool) * type.vecsize * type.columns;
			break;
		}
		case spirv_cross::SPIRType::SByte:
		{
			switch (type.vecsize)
			{
			case 1: data.format = VK_FORMAT_R8_SINT; break;
			case 2: data.format = VK_FORMAT_R8G8_SINT; break;
			case 3: data.format = VK_FORMAT_R8G8B8_SINT; break;
			case 4: data.format = VK_FORMAT_R8G8B8A8_SINT; break;
			default: data.format = VK_FORMAT_UNDEFINED;
			}
			data.size = sizeof(int8_t) * type.vecsize * type.columns;
			break;
		}
		case spirv_cross::SPIRType::UByte:
		{
			switch (type.vecsize)
			{
			case 1: data.format = VK_FORMAT_R32_UINT; break;
			case 2: data.format = VK_FORMAT_R32G32_UINT; break;
			case 3: data.format = VK_FORMAT_R32G32B32_UINT; break;
			case 4: data.format = VK_FORMAT_R32G32B32A32_UINT; break;
			default: data.format = VK_FORMAT_UNDEFINED;
			}
			data.size = sizeof(uint8_t) * type.vecsize * type.columns;
			break;
		}
		case spirv_cross::SPIRType::Short:
		{
			switch (type.vecsize)
			{
			case 1: data.format = VK_FORMAT_R16_SINT; break;
			case 2: data.format = VK_FORMAT_R16G16_SINT; break;
			case 3: data.format = VK_FORMAT_R16G16B16_SINT; break;
			case 4: data.format = VK_FORMAT_R16G16B16A16_SINT; break;
			default: data.format = VK_FORMAT_UNDEFINED;
			}
			data.size = sizeof(int16_t) * type.vecsize * type.columns;
			break;
		}
		case spirv_cross::SPIRType::UShort:
		{
			switch (type.vecsize)
			{
			case 1: data.format = VK_FORMAT_R16_UINT; break;
			case 2: data.format = VK_FORMAT_R16G16_UINT; break;
			case 3: data.format = VK_FORMAT_R16G16B16_UINT; break;
			case 4: data.format = VK_FORMAT_R16G16B16A16_UINT; break;
			default: data.format = VK_FORMAT_UNDEFINED;
			}
			data.size = sizeof(uint16_t) * type.vecsize * type.columns;
			break;
		}
		case spirv_cross::SPIRType::Int:
		{
			switch (type.vecsize)
			{
			case 1: data.format = VK_FORMAT_R32_SINT; break;
			case 2: data.format = VK_FORMAT_R32G32_SINT; break;
			case 3: data.format = VK_FORMAT_R32G32B32_SINT; break;
			case 4: data.format = VK_FORMAT_R32G32B32A32_SINT; break;
			default: data.format = VK_FORMAT_UNDEFINED;
			}
			data.size = sizeof(int32_t) * type.vecsize * type.columns;
			break;
		}
		case spirv_cross::SPIRType::UInt:
		{
			switch (type.vecsize)
			{
			case 1: data.format = VK_FORMAT_R32_UINT; break;
			case 2: data.format = VK_FORMAT_R32G32_UINT; break;
			case 3: data.format = VK_FORMAT_R32G32B32_UINT; break;
			case 4: data.format = VK_FORMAT_R32G32B32A32_UINT; break;
			default: data.format = VK_FORMAT_UNDEFINED;
			}
			data.size = sizeof(uint32_t) * type.vecsize * type.columns;
			break;
		}
		case spirv_cross::SPIRType::Int64:
		{
			switch (type.vecsize)
			{
			case 1: data.format = VK_FORMAT_R64_SINT; break;
			case 2: data.format = VK_FORMAT_R64G64_SINT; break;
			case 3: data.format = VK_FORMAT_R64G64B64_SINT; break;
			case 4: data.format = VK_FORMAT_R64G64B64A64_SINT; break;
			default: data.format = VK_FORMAT_UNDEFINED;
			}
			data.size = sizeof(int64_t) * type.vecsize * type.columns;
			break;
		}
		case spirv_cross::SPIRType::UInt64:
		{
			switch (type.vecsize)
			{
			case 1: data.format = VK_FORMAT_R64_UINT; break;
			case 2: data.format = VK_FORMAT_R64G64_UINT; break;
			case 3: data.format = VK_FORMAT_R64G64B64_UINT; break;
			case 4: data.format = VK_FORMAT_R64G64B64A64_UINT; break;
			default: data.format = VK_FORMAT_UNDEFINED;
			}
			data.size = sizeof(uint64_t) * type.vecsize * type.columns;
			break;
		}
		case spirv_cross::SPIRType::AtomicCounter:
		{
			data.format = VK_FORMAT_UNDEFINED;
			data.size = 0;
			break;
		}
		case spirv_cross::SPIRType::Half:
		{
			switch (type.vecsize)
			{
			case 1: data.format = VK_FORMAT_R16_SFLOAT; break;
			case 2: data.format = VK_FORMAT_R16G16_SFLOAT; break;
			case 3: data.format = VK_FORMAT_R16G16B16_SFLOAT; break;
			case 4: data.format = VK_FORMAT_R16G16B16A16_SFLOAT; break;
			default: data.format = VK_FORMAT_UNDEFINED;
			}
			constexpr uint32_t halfSize = sizeof(float) / 2;
			data.size = halfSize * type.vecsize * type.columns;
			break;
		}
		case spirv_cross::SPIRType::Float:
		{
			switch (type.vecsize)
			{
			case 1: data.format = VK_FORMAT_R32_SFLOAT; break;
			case 2: data.format = VK_FORMAT_R32G32_SFLOAT; break;
			case 3: data.format = VK_FORMAT_R32G32B32_SFLOAT; break;
			case 4: data.format = VK_FORMAT_R32G32B32A32_SFLOAT; break;
			default: data.format = VK_FORMAT_UNDEFINED;
			}
			data.size = sizeof(float) * type.vecsize * type.columns;
			break;
		}
		case spirv_cross::SPIRType::Double:
		{
			switch (type.vecsize)
			{
			case 1: data.format = VK_FORMAT_R64_SFLOAT; break;
			case 2: data.format = VK_FORMAT_R64G64_SFLOAT; break;
			case 3: data.format = VK_FORMAT_R64G64B64_SFLOAT; break;
			case 4: data.format = VK_FORMAT_R64G64B64A64_SFLOAT; break;
			default: data.format = VK_FORMAT_UNDEFINED;
			}
			data.size = sizeof(double) * type.vecsize * type.columns;
			break;
		}
		case spirv_cross::SPIRType::Struct:
		case spirv_cross::SPIRType::SampledImage:
		case spirv_cross::SPIRType::Sampler:
		case spirv_cross::SPIRType::AccelerationStructure:
		case spirv_cross::SPIRType::RayQuery:
		case spirv_cross::SPIRType::ControlPointArray:
		case spirv_cross::SPIRType::Interpolant:
		case spirv_cross::SPIRType::Char:
		default:
		{
			data.format = VK_FORMAT_UNDEFINED;
			data.size = 0;
			break;
		}
		}

		return data;
	}
}
