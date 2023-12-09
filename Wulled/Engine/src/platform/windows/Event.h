#pragma once
#include "Engine/src/core/EngineCore.h"
#include "Engine/src/core/Events/windowEvent.h"


namespace WLD
{
	class WLD_API WinEvent : public WinEventCallBack
	{
	public:
		WinEvent();
		virtual ~WinEvent() override;

		LRESULT callEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;

		virtual inline void setCursorPosCallback  (std::function<void(HWND, int, int          )> func) override { m_CursorPosCallback    = func; }
		virtual inline void SetWindowCloseCallback(std::function<void(HWND                    )> func) override { m_WindowCloseCallback  = func; }
		virtual inline void SetWindowSizeCallback (std::function<void(HWND, int, int          )> func) override { m_WindowResizeCallback = func; }
		virtual inline void SetKeyCallback        (std::function<void(HWND, int, int, int, int)> func) override { m_KeyCallback          = func; }
//		virtual inline void SetCharCallback       (std::function<void(HWND, uint32_t          )> func) override { m_CharCallback         = func; }
		virtual inline void SetMouseButtonCallback(std::function<void(HWND, int, int, int     )> func) override { m_MouseButtonCallback  = func; }
		virtual inline void SetScrollCallback     (std::function<void(HWND, double, double    )> func) override { m_ScrollCallback       = func; }

	private:
		// functions
		std::function<void(HWND, int, int          )> m_CursorPosCallback   ;
		std::function<void(HWND                    )> m_WindowCloseCallback ;
		std::function<void(HWND, int, int          )> m_WindowResizeCallback;
		std::function<void(HWND, int, int, int, int)> m_KeyCallback         ;
//		std::function<void(HWND, uint32_t          )> m_CharCallback        ;
		std::function<void(HWND, int, int, int     )> m_MouseButtonCallback ;
		std::function<void(HWND, double, double    )> m_ScrollCallback      ;
	};
}