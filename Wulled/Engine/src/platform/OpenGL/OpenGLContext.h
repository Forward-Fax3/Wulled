#pragma once
#include "Engine/src/core/EngineCore.h"

#include "Engine/src/core/graphics/GraphicsContext.h"


struct GLFWwindow;

namespace WLD::Graphics::OpenGL
{
	class WLD_API OpenGLContext : public Renderer::GraphicsContext
	{
	public:
		OpenGLContext(HWND* windowHandle);

		virtual void Init() override;
		virtual void Shutdown() override;
		virtual void SwapBuffers() override;
		virtual void OnWindowResize(uint32_t width, uint32_t height) override;

		virtual void makeCurrent() override;

	private:
		HWND* m_WindowHandle;
		HDC m_HDC;
		HGLRC m_hglrc;
		PIXELFORMATDESCRIPTOR m_pfd;
	};
}


