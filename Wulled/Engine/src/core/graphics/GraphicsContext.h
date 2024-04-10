#pragma once
#include <windows.h>
#include "Engine/src/core/EngineCore.h"


namespace WLD
{
	struct WLD_API WindowProps;
}

namespace WLD::Graphics
{
	class WLD_API GraphicsContext
	{
	public:
		virtual void CreateDevice() = 0;
		virtual void Shutdown() = 0;
		virtual void SwapBuffers() = 0;
		virtual void OnWindowResize(uint32_t width, uint32_t height) = 0;
		virtual void MakeCurrent() = 0;
		virtual void Info() = 0;

		static GraphicsContext* createGraphicsContext(HWND* window, const WindowProps& Data);
	};
}

#include "Engine/src/core/Window.h"