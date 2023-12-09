#include "wldpch.h"
#include "Window.h"
#include "EngineCore.h"
#include "log.h"

#include "Windows/Window.h"


namespace WLD
{
	Window* Window::Create(const WindowProps& props)
	{
		Window* window = new(std::nothrow) WinWindow(props);
		WLD_CORE_ASSERT(window, "Failed to create window!");
		return window;
	}
}