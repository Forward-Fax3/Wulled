#include"wldpch.h"
#include "log.h"

#include "OpenGLContext.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"


namespace WLD::Graphics::OpenGL
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		WLD_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int32_t status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		WLD_CORE_ASSERT(status, "Failed to initialize Glad!");

		WLD_CORE_INFO
		(
			"OpenGL Info:\n"
			"\t\t\t  OpenGL Version: {0}\n"
			"\t\t\t  OpenGL Renderer: {1}\n"
			"\t\t\t  OpenGL Version: {2}",
			(const char*)glGetString(GL_VENDOR),   // 0
			(const char*)glGetString(GL_RENDERER), // 1
			(const char*)glGetString(GL_VERSION)   // 2
		);
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
