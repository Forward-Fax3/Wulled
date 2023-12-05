#include "wldpch.h"
#include "Window.h"
#include "EngineCore.h"
#include "log.h"

#include "WinWindow.h"


namespace WLD
{
	Window* Window::Create(const WindowProps& props)
	{
		Window* window = new(std::nothrow) WinWindow(props);
		WLD_ASSERT(window, "Failed to create window!");
		return window;
	}
}