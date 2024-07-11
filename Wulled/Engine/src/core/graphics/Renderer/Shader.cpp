#include "WLDPCH.h"
#include "EngineCore.h"
#include "WLDMem.h"

#include "Renderer.h"
#include "WLDFileStream.h"

#include "Shader.h"
#include "OpenGLShader.h"
#include "VkShader.h"


namespace WLD
{
	Shader* Shader::Create(const std::vector<InputShader>& shaders)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: WLD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:    return CreateMemory(OpenGLShader, shaders);
		case RendererAPI::API::Vulkan:    return CreateMemory(VulkanShader, shaders);

		default: WLD_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
		}
	}

	std::vector<uint32_t> Shader::CompileToVkSPIRV(const std::string& source, const std::string& filePath, shaderc_shader_kind shaderType) const
	{
		shaderc::Compiler* compiler = CreateMemory(shaderc::Compiler);
		shaderc::CompileOptions options;
		options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_3);
		options.SetSourceLanguage(shaderc_source_language_glsl);
		shaderc::SpvCompilationResult module = compiler->CompileGlslToSpv(source, shaderType, "shader", options);
		WLD_CORE_ASSERT(module.GetCompilationStatus() == shaderc_compilation_status_success, "Shader compilation failed: {0}", module.GetErrorMessage());
		std::vector<uint32_t> vulkanSPIRV(module.cbegin(), module.cend());

		FileStream::WriteFile(filePath + ".spv", vulkanSPIRV);
		DestroyMemory(compiler);
		return vulkanSPIRV;
	}
}