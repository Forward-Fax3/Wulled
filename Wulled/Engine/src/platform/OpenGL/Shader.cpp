#include "wldpch.h"
// #define EN_ENABLE_ASSERTS
#include "OpenGL/Shader.h"
#include "glm/gtc/type_ptr.hpp"

#include "glatter/glatter.h"


namespace WLD::Graphics::OpenGL
{
	OpenGLShader::OpenGLShader(const std::string_view& vertexSrc, const std::string_view& fragmentSrc)
	{
		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = (const GLchar*)vertexSrc.data();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.

			WLD_CORE_ASSERT
			(
				false,
				"Vertex shader compilation failure! {1}",
				infoLog.data()
			);
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const GLchar*)fragmentSrc.data();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.

			WLD_CORE_ASSERT
			(
				false,
				"Fragment shader compilation failure!\n"
				"{0}",
				infoLog.data()
			);
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_RendererID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);

		// Link our program
		glLinkProgram(m_RendererID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_RendererID);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			// Use the infoLog as you see fit.

			WLD_CORE_ASSERT
			(
				false,
				"{0}\n"
				"Shader link failure!",
				infoLog.data()
			);
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);
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
}