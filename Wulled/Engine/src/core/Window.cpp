#include "wldpch.h"
#include "EngineCore.h"
#include "WLDMem.h"
#include "Window.h"

#include "Windows/Window.h"


namespace WLD
{
	Ref<Window> Window::Create(const WindowProps& props)
	{
		return CreateRef(WinWindow, props);
	}
}