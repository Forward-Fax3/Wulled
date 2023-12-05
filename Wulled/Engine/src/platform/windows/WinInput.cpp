#include "wldpch.h"

#include "EngineCore.h"
#include "WinInput.h"
#include "application.h"
#include "KeyCodes.h"
#include "MouseButtonCodes.h"
#include <Window.h>

#include "glatter/glatter.h"

namespace WLD
{

	std::unique_ptr<Input> Input::s_Instance = std::make_unique<WindowsInput>();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		return GetAsyncKeyState(WLDKeyToVKey(keycode));
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		return GetAsyncKeyState(WLDMouseToVKMouse(button));
	}

	std::pair<LONG, LONG> WindowsInput::GetMousePositionImpl()
	{
		POINT point;
		GetCursorPos(&point);

		return std::pair<LONG, LONG>(point.x, point.y);
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