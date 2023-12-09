#pragma once
#include "Engine/src/core/EngineCore.h"

#include "Engine/src/core/graphics/GraphicsContext.h"


namespace WLD::Graphics::OpenGL
{
	class WLD_API OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(HWND* windowHandle);

		virtual void CreateDevice() override;
		virtual void Shutdown() override;
		virtual void SwapBuffers() override;
		virtual void OnWindowResize(uint32_t width, uint32_t height) override;
		virtual void MakeCurrent() override;

		virtual void Info() override;

	private:
		HWND* m_WindowHandle;
		HDC m_HDC;
		bool m_IsInitialized = false;
		
		static inline HGLRC s_hglrc;
	};
}


