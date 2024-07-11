#include "WLDPCH.h"

#include "EngineCore.h"
#include "WinInput.h"
#include "Application.h"
#include "KeyCodes.h"
#include "MouseButtonCodes.h"
#include <Window.h>

#include "GL/glew.h"
// #include "glad/glad.h"

namespace WLD
{

	std::unique_ptr<Input> Input::s_Instance = std::make_unique<WindowsInput>();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		return GetAsyncKeyState(WLDKeyToSDLKey(keycode));
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		return GetAsyncKeyState(WLDMouseToSDLMouse(button));
	}

	std::pair<int32_t, int32_t> WindowsInput::GetMousePositionImpl()
	{
		POINT point;
		GetCursorPos(&point);

		return std::pair<int32_t, int32_t>((int32_t)point.x, (int32_t)point.y);
	}

	double WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}

	double WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}
}