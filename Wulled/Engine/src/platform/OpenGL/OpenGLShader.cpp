#include "wldpch.h"
#include "WLDMem.h"
// #define EN_ENABLE_ASSERTS
#include "OpenGLShader.h"
#include "application.h"
#include "WLDFileStream.h"

#include "glm/gtc/type_ptr.hpp"

#include "GL/GL.h"
#include "GL/glew.h"

#include "SDL.h"

#include "spirv_cross/spirv_glsl.hpp"
#include "shaderc/shaderc.hpp"

#include <fstream>


namespace WLD
{
	OpenGLShader::OpenGLShader(const std::vector<InputShader>& shaders)
	{
		m_RendererID = glCreateProgram();

		std::vector<ShaderInfo> shaderSources;
		shaderSources.reserve(shaders.size());
		bool needsRecopilation = false;
		for (const auto& [type, baseFilePath] : shaders)
		{
			std::string filePath = "assets/shaders/" + baseFilePath;
			std::vector<uint32_t> OGL_SPIR_V;

			if (!FileStream::ReadFile(filePath + ".OGL.spv", OGL_SPIR_V))
			{
				needsRecopilation = true;
				break; // if any of the shaders are missing, we need to recompile all of them so that we can make sure that the push constants are in the right order and have the right locations
			}
			shaderSources.emplace_back(type, OGL_SPIR_V);
		}

		if (needsRecopilation)
		{
			shaderSources.clear();
			int32_t pushConstsLocations = 0;
			for (const auto& [type, baseFilePath] : shaders)
			{
				std::string filePath = "assets/shaders/" + baseFilePath;
				std::vector<uint32_t> OGL_SPIR_V;
				if (GetOGLSPIRVfromVkSPIRVOrSource(filePath, type, pushConstsLocations, OGL_SPIR_V))
					shaderSources.emplace_back(type, OGL_SPIR_V);
				else LOG_CORE_ERROR
				(
					"Failed to get shader at \"{0}\"\n"
					"this shader file will not be included into shader\n"
					"this shader may not work as expected.",
					baseFilePath
				);
			}
		}
		Compile(shaderSources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		glUniform1i(glGetUniformLocation(m_RendererID, name.data()), value);
	}

	void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
	{
		glUniform1iv(glGetUniformLocation(m_RendererID, name.data()), count, values);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		glUniform1f(glGetUniformLocation(m_RendererID, name.data()), value);
	}

	void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value)
	{
		glUniform2f(glGetUniformLocation(m_RendererID, name.data()), value.x, value.y);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		glUniform3f(glGetUniformLocation(m_RendererID, name.data()), value.x, value.y, value.z);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		glUniform4f(glGetUniformLocation(m_RendererID, name.data()), value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetMat2(const std::string& name, const glm::mat2& value)
	{
		glUniformMatrix2fv(glGetUniformLocation(m_RendererID, name.data()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::SetMat3(const std::string& name, const glm::mat3& value)
	{
		glUniformMatrix3fv(glGetUniformLocation(m_RendererID, name.data()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_RendererID, name.data()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::SetPushConst(const std::string& UBName, const std::vector< PushConstOpaqueObj>& layout, const void* data)
	{
		if (m_PushConstantsLocations.find(UBName) == m_PushConstantsLocations.end())
		{
			LOG_CORE_ERROR("Uniform Buffer {0} not found", UBName);
			return;
		}
		GLint currentLayout = m_PushConstantsLocations[UBName];
		size_t dataOffset = 0;

		for (const auto& opaqueType : layout)
		{
			void* currentDataPtr = (void*)((size_t)data + dataOffset);
			switch (opaqueType.type)
			{
			case ShaderDataType::None:
				LOG_CORE_ERROR("ShaderDataType::None is not supported: {0}", __FILE__);
				break;
			case ShaderDataType::Bool:
			{
				int* value = CreateArray(int, opaqueType.arraySize);
				for (uint32_t i = 0; i < opaqueType.arraySize; i++)
					value[i] = ((bool*)currentDataPtr)[i];
				glUniform1iv(currentLayout, opaqueType.arraySize, value);
				dataOffset += 1ui64 * opaqueType.arraySize;
				DestroyArray(value);
				break;
			}
			case ShaderDataType::Int:
				glUniform1iv(currentLayout, opaqueType.arraySize, (int*)currentDataPtr);
				dataOffset += 4ui64 * opaqueType.arraySize;
				break;
			case ShaderDataType::Int2:
				glUniform2iv(currentLayout, opaqueType.arraySize, (int*)currentDataPtr);
				dataOffset += 8ui64 * opaqueType.arraySize;
				break;
			case ShaderDataType::Int3:
				glUniform3iv(currentLayout, opaqueType.arraySize, (int*)currentDataPtr);
				dataOffset += 12ui64 * opaqueType.arraySize;
				break;
			case ShaderDataType::Int4:
				glUniform4iv(currentLayout, opaqueType.arraySize, (int*)currentDataPtr);
				dataOffset += 16ui64 * opaqueType.arraySize;
				break;
			case ShaderDataType::Float:
				glUniform1fv(currentLayout, opaqueType.arraySize, (float*)currentDataPtr);
				dataOffset += 4ui64 * opaqueType.arraySize;
				break;
			case ShaderDataType::Float2:
				glUniform2fv(currentLayout, opaqueType.arraySize, (float*)currentDataPtr);
				dataOffset += 8ui64 * opaqueType.arraySize;
				break;
			case ShaderDataType::Float3:
				glUniform3fv(currentLayout, opaqueType.arraySize, (float*)currentDataPtr);
				dataOffset += 12ui64 * opaqueType.arraySize;
				break;
			case ShaderDataType::Float4:
				glUniform4fv(currentLayout, opaqueType.arraySize, (float*)currentDataPtr);
				dataOffset += 16ui64 * opaqueType.arraySize;
				break;
			case ShaderDataType::Mat2:
				glUniformMatrix2fv(currentLayout, opaqueType.arraySize, GL_FALSE, (float*)currentDataPtr);
				dataOffset += 16ui64 * opaqueType.arraySize;
				break;
			case ShaderDataType::Mat3:
				glUniformMatrix3fv(currentLayout, opaqueType.arraySize, GL_FALSE, (float*)currentDataPtr);
				dataOffset += 36ui64 * opaqueType.arraySize;
				break;
			case ShaderDataType::Mat4:
				glUniformMatrix4fv(currentLayout, opaqueType.arraySize, GL_FALSE, (float*)currentDataPtr);
				dataOffset += 64ui64 * opaqueType.arraySize;
				break;
			case ShaderDataType::Mat2x3:
				glUniformMatrix2x3fv(currentLayout, opaqueType.arraySize, GL_FALSE, (float*)currentDataPtr);
				dataOffset += 24ui64 * opaqueType.arraySize;
				break;
			case ShaderDataType::Mat2x4:
				glUniformMatrix2x4fv(currentLayout, opaqueType.arraySize, GL_FALSE, (float*)currentDataPtr);
				dataOffset += 32ui64 * opaqueType.arraySize;
				break;
			case ShaderDataType::Mat3x2:
				glUniformMatrix3x2fv(currentLayout, opaqueType.arraySize, GL_FALSE, (float*)currentDataPtr);
				dataOffset += 24ui64 * opaqueType.arraySize;
				break;
			case ShaderDataType::Mat3x4:
				glUniformMatrix3x4fv(currentLayout, opaqueType.arraySize, GL_FALSE, (float*)currentDataPtr);
				dataOffset += 48ui64 * opaqueType.arraySize;
				break;
			case ShaderDataType::Mat4x2:
				glUniformMatrix4x2fv(currentLayout, opaqueType.arraySize, GL_FALSE, (float*)currentDataPtr);
				dataOffset += 32ui64 * opaqueType.arraySize;
				break;
			case ShaderDataType::Mat4x3:
				glUniformMatrix4x3fv(currentLayout, opaqueType.arraySize, GL_FALSE, (float*)currentDataPtr);
				dataOffset += 48ui64 * opaqueType.arraySize;
				break;
			}
			currentLayout += opaqueType.arraySize;
		}
	}

	void OpenGLShader::Compile(const std::vector<ShaderInfo>& shaderSources)
	{
		std::vector<GLuint> glShaderIDs;
		glShaderIDs.reserve(shaderSources.size());
//		int32_t pushConstsLocations = 0;

		for (const auto& [type, source] : shaderSources) 
		{
			Reflect(source);

			GLuint glShader = glShaderIDs.emplace_back(glCreateShader(GetOGLShaderTypeFromWLDShaderType(type)));
			glShaderBinary(1, &glShader, GL_SHADER_BINARY_FORMAT_SPIR_V, (const GLchar*)source.data(), (GLsizei)source.size() * sizeof(uint32_t));
			const char* const entryPoint = "main";
			glSpecializeShader(glShader, entryPoint, 0, nullptr, nullptr);
			glAttachShader(m_RendererID, glShader);
		}

		glLinkProgram(m_RendererID);

		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(m_RendererID);

			for (auto id : glShaderIDs)
				glDeleteShader(id);

			LOG_CORE_FATAL
			(
				"{0}\n"
				"Shader link failure!",
				infoLog.data()
			);
		}

		for (GLuint id : glShaderIDs)
			glDetachShader(m_RendererID, id);
	}

	bool OpenGLShader::GetOGLSPIRVfromVkSPIRVOrSource(const std::string& filePath, WLD_ShaderType Type, int32_t& pushConstsLocations, std::vector<uint32_t>& result)
	{
		std::vector<uint32_t> VkSPIRV;
		shaderc_shader_kind shaderType = GetShadercShaderKindFromWLDShaderType(Type);
		if (!FileStream::ReadFile(filePath + ".spv", VkSPIRV))
		{
			std::string GLSLSource;
			if (!FileStream::ReadFile(filePath, GLSLSource))
				return false;

			VkSPIRV = CompileToVkSPIRV(GLSLSource, filePath, shaderType);
		}

		result = CrossCompile(VkSPIRV, filePath, pushConstsLocations, shaderType);
		return true;
	}

	std::vector<uint32_t> OpenGLShader::CrossCompile(const std::vector<uint32_t>& shaderSource, const std::string& filePath, int32_t& pushConstsLocations, shaderc_shader_kind shaderType)
	{
		spirv_cross::CompilerGLSL* crossCompiler = CreateMemory(spirv_cross::CompilerGLSL, shaderSource);
		spirv_cross::ShaderResources* resources = CreateMemory(spirv_cross::ShaderResources);
		spirv_cross::CompilerGLSL::Options GLSLOptions;
		*resources = crossCompiler->get_shader_resources();

		for (const auto& resource : resources->push_constant_buffers)
		{
			crossCompiler->set_decoration(resource.id, spv::DecorationLocation, pushConstsLocations); // sets the location of the push constant for when it becomes a plain uniform
			auto& type = crossCompiler->get_type(resource.base_type_id);
			for (size_t i = 0; i < type.member_types.size(); i++)
			{
				const auto& array = crossCompiler->get_type(type.member_types[i]).array;
				uint32_t arraySize = 1; // a default value of 1
				if (array.size()) // checks to see if the member is an array
					arraySize = array.front(); // sets the array size to the first element of the array which is the size of the array
				pushConstsLocations += arraySize;
			}
		}

		GLSLOptions.version = 450;
		GLSLOptions.es = false;
		crossCompiler->set_common_options(GLSLOptions);

		std::string OpenGL_GLSL(crossCompiler->compile());
		DestroyMemory(resources);

		DestroyMemory(crossCompiler);
#ifdef _DEBUG
		FileStream::WriteFile(filePath + ".OGL", OpenGL_GLSL);
#endif

		shaderc::Compiler* compiler = CreateMemory(shaderc::Compiler);
		shaderc::CompileOptions options;
		options.SetTargetEnvironment(shaderc_target_env_opengl, shaderc_env_version_opengl_4_5);
		options.SetSourceLanguage(shaderc_source_language_glsl);
		shaderc::SpvCompilationResult module = compiler->CompileGlslToSpv(OpenGL_GLSL, shaderType, "shader", options);
		WLD_CORE_ASSERT(module.GetCompilationStatus() == shaderc_compilation_status_success, "Shader compilation failed: {0}", module.GetErrorMessage());

		std::vector<uint32_t> GLSL_SPIR_V(module.cbegin(), module.cend());
		FileStream::WriteFile(filePath + ".OGL.spv", GLSL_SPIR_V);

		DestroyMemory(compiler);
		return GLSL_SPIR_V;
	}

	void OpenGLShader::Reflect(const std::vector<uint32_t>& shaderSource)
	{
		spirv_cross::Compiler* compiler = CreateMemory(spirv_cross::Compiler, shaderSource);
		spirv_cross::ShaderResources* resources = CreateMemory(spirv_cross::ShaderResources);
		*resources = compiler->get_shader_resources();
		for (const auto& resource : resources->gl_plain_uniforms)
			m_PushConstantsLocations.insert(std::pair(resource.name, compiler->get_decoration(resource.id, spv::DecorationLocation))); // get the start location of the struct uniform buffer and pairs it with the name of the uniform

		DestroyMemory(resources);
		DestroyMemory(compiler);
	}

	GLenum OpenGLShader::GetOGLShaderTypeFromWLDShaderType(WLD_ShaderType type) const
	{
		switch (type)
		{
		case WLD_ShaderType::None:     return GL_INVALID_ENUM;
		case WLD_ShaderType::Vertex:   return GL_VERTEX_SHADER;
		case WLD_ShaderType::Fragment: return GL_FRAGMENT_SHADER;
		}

		LOG_CORE_FATAL("unknown shader type");
		return GL_INVALID_ENUM;
	}

	shaderc_shader_kind OpenGLShader::GetShadercShaderKindFromWLDShaderType(WLD_ShaderType type) const
	{
		switch (type)
		{
		case WLD_ShaderType::None:     return (shaderc_shader_kind)-1;
		case WLD_ShaderType::Vertex:   return shaderc_glsl_vertex_shader;
		case WLD_ShaderType::Fragment: return shaderc_glsl_fragment_shader;
		}

		LOG_CORE_FATAL("unkown shader type");
		return (shaderc_shader_kind)-1;
	}
}
