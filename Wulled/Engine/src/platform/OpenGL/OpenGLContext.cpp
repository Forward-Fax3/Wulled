#include"wldpch.h"
#include "log.h"

#include "Application.h"
#include "OpenGLContext.h"
#include "glatter/glatter.h"

bool glSwapBuffers(HDC hdc)
{
	return SwapBuffers(hdc);
}


namespace WLD::Graphics::OpenGL
{
	OpenGLContext::OpenGLContext(HWND* windowHandle)
		: m_WindowHandle(windowHandle), m_HDC(nullptr)
	{
		WLD_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		m_pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
			PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
			32,                   // Colordepth of the framebuffer.
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24,                   // Number of bits for the depthbuffer
			8,                    // Number of bits for the stencilbuffer
			0,                    // Number of Aux buffers in the framebuffer.
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};

		m_HDC = GetDC(*m_WindowHandle);

		SetPixelFormat(m_HDC, ChoosePixelFormat(m_HDC, &m_pfd), &m_pfd);

		m_hglrc = wglCreateContext(m_HDC);
		wglMakeCurrent(m_HDC, m_hglrc);

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

	void OpenGLContext::Shutdown()
	{
		wglMakeCurrent(m_HDC, NULL);
		wglDeleteContext(m_hglrc);
	}

	void OpenGLContext::SwapBuffers()
	{
//		glfwSwapBuffers(m_WindowHandle);
		glSwapBuffers(m_HDC);
	}

	void OpenGLContext::OnWindowResize(uint32_t width, uint32_t height)
	{
//		glfwSetWindowSize(static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow()), width, height);
		glViewport(0, 0, width, height);
	}

	void OpenGLContext::makeCurrent()
	{
		wglMakeCurrent(m_HDC, m_hglrc);
	}
}
