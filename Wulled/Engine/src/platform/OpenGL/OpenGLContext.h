#pragma once
#include "Engine/src/core/EngineCore.h"

#include "Engine/src/core/Renderer/GraphicsContext.h"


struct GLFWwindow;

namespace WLD
{
	class WLD_API OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		void Init() override;
		void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};
}


