#include "wldpch.h"
// #define EN_ENABLE_ASSERTS
#include "OpenGL/Shader.h"
#include "glm/gtc/type_ptr.hpp"

#include "glatter/glatter.h"

#include <fstream>


namespace WLD::Graphics::OpenGL
{
	GLenum ShaderTypeFromString(const std::string_view& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		WLD_CORE_FATAL("unkown shader type");
	}

	OpenGLShader::OpenGLShader(const std::string_view& filepath)
	{
		std::string source = ReadFile(filepath);
		std::unordered_map<GLenum, std::string> shaderSources = PreProcess(source);
		Compile(shaderSources);

	}

	OpenGLShader::OpenGLShader(const std::string_view& vertexSrc, const std::string_view& fragmentSrc)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(sources);
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

	void OpenGLShader::SetUniformInt(std::string_view name, const int value)
	{
		glUniform1i(glGetUniformLocation(m_RendererID, name.data()), value);
	}

	void OpenGLShader::SetUniformFloat(std::string_view name, const float value)
	{
		glUniform1f(glGetUniformLocation(m_RendererID, name.data()), value);
	}

	void OpenGLShader::SetUniformFloat2(std::string_view name, const glm::vec2& values)
	{
		glUniform2f(glGetUniformLocation(m_RendererID, name.data()), values.x, values.y);
	}

	void OpenGLShader::SetUniformFloat3(std::string_view name, const glm::vec3& values)
	{
		glUniform3f(glGetUniformLocation(m_RendererID, name.data()), values.x, values.y, values.z);
	}

	void OpenGLShader::SetUniformFloat4(std::string_view name, const glm::vec4& values)
	{
		glUniform4f(glGetUniformLocation(m_RendererID, name.data()), values.x, values.y, values.z, values.w);
	}

	void OpenGLShader::SetUniformMat2fv(std::string_view name, const glm::mat2& matrix)
	{
		glUniformMatrix2fv(glGetUniformLocation(m_RendererID, name.data()), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::SetUniformMat3fv(std::string_view name, const glm::mat3& matrix)
	{
		glUniformMatrix3fv(glGetUniformLocation(m_RendererID, name.data()), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::SetUniformMat4fv(std::string_view name, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_RendererID, name.data()), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	std::string OpenGLShader::ReadFile(const std::string_view& filepath)
	{
		std::string result;
		std::ifstream in(filepath.data(), std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			WLD_CORE_ERROR("Could not open file: {0}", filepath);
			result = filepath;
		}
		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string_view& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			WLD_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type(source.substr(begin, eol - begin));

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		GLuint program = glCreateProgram();
		std::vector<GLuint> glShaderIDs(shaderSources.size());

		for (auto& currentShader : shaderSources)
		{
			GLenum shaderType = currentShader.first;
			const std::string_view& shaderSource = currentShader.second;

			GLuint glShader = glCreateShader(shaderType);

			const GLchar* glSource = (const GLchar*)shaderSource.data();
			glShaderSource(glShader, 1, &glSource, 0);

			glCompileShader(glShader);

			GLint isCompiled = 0;
			glGetShaderiv(glShader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(glShader, GL_INFO_LOG_LENGTH, &maxLength);
	
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(glShader, maxLength, &maxLength, &infoLog[0]);
	
				glDeleteShader(glShader);
	
				WLD_CORE_ASSERT
				(
					false,
					"Shader compilation failure! {0}",
					infoLog.data()
				);
			}

			glAttachShader(program, glShader);
			glShaderIDs.push_back(glShader);
		}

		m_RendererID = program;

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

			WLD_CORE_ASSERT
			(
				false,
				"{0}\n"
				"Shader link failure!",
				infoLog.data()
			);
		}

		for (auto id : glShaderIDs)
			glDetachShader(m_RendererID, id);
	}
}