#include "wldpch.h"
#include "WinEvent.h"
#include "KeyCodes.h"
#include "MouseButtonCodes.h"
#include "backends/imgui_impl_win32.h"
#include <windowsx.h>


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace WLD
{
	WinEvent::WinEvent()
	{
	}

	WinEvent::~WinEvent()
	{
	}

	LRESULT WinEvent::callEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam))
			return true;

		switch (uMsg)
		{
		case WM_CLOSE:
			m_WindowCloseCallback(hwnd);
			return true;
		case WM_SIZE:
{
			int width = LOWORD(lParam);
			int height = HIWORD(lParam);
			if (m_WindowResizeCallback)
				m_WindowResizeCallback(hwnd, width, height);
			return true;
		}
		case WM_KEYDOWN:
		{
			m_KeyCallback(hwnd, wParam, NULL, WLD_PRESS, NULL);
			return true;
		}
		case WM_KEYUP:
		{
			m_KeyCallback(hwnd, wParam, NULL, WLD_RELEASE, NULL);
			return true;
		}
		case WM_LBUTTONDOWN:
		{
			m_MouseButtonCallback(hwnd, WLD_MOUSE_BUTTON_LEFT, WLD_PRESS, 0);
			return true;
		}
		case WM_LBUTTONUP:
		{
			m_MouseButtonCallback(hwnd, WLD_MOUSE_BUTTON_LEFT, WLD_RELEASE, 0);
			return true;
		}
		case WM_MBUTTONDOWN:
		{
			m_MouseButtonCallback(hwnd, WLD_MOUSE_BUTTON_MIDDLE, WLD_PRESS, 0);
			return true;
		}
		case WM_MBUTTONUP:
		{
			m_MouseButtonCallback(hwnd, WLD_MOUSE_BUTTON_MIDDLE, WLD_RELEASE, 0);
			return true;
		}
		case WM_RBUTTONDOWN:
		{
			m_MouseButtonCallback(hwnd, WLD_MOUSE_BUTTON_RIGHT, WLD_PRESS, 0);
			return true;
		}
		case WM_RBUTTONUP:
		{
			m_MouseButtonCallback(hwnd, WLD_MOUSE_BUTTON_RIGHT, WLD_RELEASE, 0);
			return true;
		}
		case WM_MOUSEWHEEL:
		{
			int delta = GET_WHEEL_DELTA_WPARAM(wParam);
			m_ScrollCallback(hwnd, (double)0, (double)delta);
			return true;
		}
		case WM_MOUSEMOVE:
		{
			int xpos = GET_X_LPARAM(lParam);
			int ypos = GET_Y_LPARAM(lParam);

			m_CursorPosCallback(hwnd, xpos, ypos);
			return true;
		}
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			// All painting occurs here, between BeginPaint and EndPaint.

			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

			EndPaint(hwnd, &ps);
			return true;
		}
		default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}
}