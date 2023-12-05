#pragma once
#include "Engine/src/core/EngineCore.h"


namespace WLD::Graphics::Renderer
{
	class WLD_API GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void Shutdown() = 0;
		virtual void SwapBuffers() = 0;
		virtual void OnWindowResize(uint32_t width, uint32_t height) = 0;

		static GraphicsContext* createGraphicsContext(HWND* window);

		virtual void makeCurrent() = 0;
	};
}
