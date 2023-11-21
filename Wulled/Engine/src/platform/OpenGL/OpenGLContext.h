#pragma once
#include "Engine/src/core/EngineCore.h"

#include "Engine/src/core/Renderer/GraphicsContext.h"


struct GLFWwindow;

namespace WLD::Graphics::OpenGL
{
	class WLD_API OpenGLContext : public Renderer::GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		void Init() override;
		void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};
}


