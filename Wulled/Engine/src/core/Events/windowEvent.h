#pragma once
#include <windows.h>
#include <functional>


namespace WLD
{
	class WLD_API WinEventCallBack
	{
	public:
		virtual ~WinEventCallBack() = default;

		virtual LRESULT callEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

		virtual void setCursorPosCallback  (std::function<void(HWND, int, int          )> func) = 0;
		virtual void SetWindowCloseCallback(std::function<void(HWND                    )> func) = 0;
		virtual void SetWindowSizeCallback (std::function<void(HWND, int, int          )> func) = 0;
		virtual void SetKeyCallback        (std::function<void(HWND, int, int, int, int)> func) = 0;
//		virtual void SetCharCallback	   (std::function<void(HWND, uint32_t          )> func) = 0;
		virtual void SetMouseButtonCallback(std::function<void(HWND, int, int, int     )> func) = 0;
		virtual void SetScrollCallback     (std::function<void(HWND, double, double    )> func) = 0;
	};
}