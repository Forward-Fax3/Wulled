#include "wldpch.h"

#include "EngineCore.h"
#include "WinInput.h"
#include "application.h"

#include <GLFW/glfw3.h>

namespace WLD
{

	std::unique_ptr<Input> Input::s_Instance = std::make_unique<WindowsInput>();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<double, double> WindowsInput::GetMousePositionImpl()
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		// std::pair<double, double> pos = std::pair<double, double>(xPos, yPos);
		return std::pair<double, double>(xPos, yPos);
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