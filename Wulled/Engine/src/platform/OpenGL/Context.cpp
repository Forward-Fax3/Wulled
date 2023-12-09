#include "wldpch.h"
#define EN_ENABLE_ASSERTS

#include "Application.h"
#include "OpenGL/Context.h"
#include "glatter/glatter.h"


namespace WLD::Graphics::OpenGL
{
	OpenGLContext::OpenGLContext(HWND* windowHandle)
		: m_WindowHandle(windowHandle), m_HDC(nullptr)
	{
		WLD_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::CreateDevice()
	{
		PIXELFORMATDESCRIPTOR PFD =
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
		WLD_CORE_ASSERT(m_HDC, "Failed to get device context!");

		int PF = ChoosePixelFormat(m_HDC, &PFD);
		WLD_CORE_ASSERT(PF, "Failed to choose pixel format!");
		WLD_CORE_ASSERT(SetPixelFormat(m_HDC, PF, &PFD), "Failed to set pixel format!");
		WLD_CORE_ASSERT(ReleaseDC(*m_WindowHandle, m_HDC), "Failed to release device context!");

		if (!s_hglrc)
			s_hglrc = wglCreateContext(m_HDC);
	}

	void OpenGLContext::Shutdown()
	{
		wglMakeCurrent(m_HDC, NULL);
		wglDeleteContext(s_hglrc);
		s_hglrc = NULL;
	}

	void OpenGLContext::SwapBuffers()
	{
		::SwapBuffers(m_HDC);
		wglSwapIntervalEXT(Application::Get().GetWindow().IsVSync());
	}

	void OpenGLContext::OnWindowResize(uint32_t width, uint32_t height)
	{
		glViewport(0, 0, width, height);
	}

	void OpenGLContext::MakeCurrent()
	{
		wglMakeCurrent(m_HDC, s_hglrc);
	}

	void OpenGLContext::Info()
	{
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
}
