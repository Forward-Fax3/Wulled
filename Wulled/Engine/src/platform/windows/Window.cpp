#include "wldpch.h"
#include "WLDMem.h"
#include "Windows/Window.h"
#include "Renderer.h"
#include "RendererAPI.h"

#include "log.h"
#include "EngineCore.h"

#include "Event.h"
#include "ApplicationEvent.h"
#include "KeyEvent.h"
#include "MouseEvent.h"
#include "application.h"
#include "Windows/Event.h"

#include "KeyCodes.h"
#include "MouseButtonCodes.h"

#include <future>

#include <windows.h>
#include <strsafe.h>


void ErrorExit(LPTSTR lpszFunction)
{
	// Retrieve the system error message for the last-error code

	LPVOID lpMsgBuf = NULL;
	DWORD dw = GetLastError();

	FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dw, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	// Display the error message and exit the process

	LPTSTR lpDisplayBuf = (LPTSTR)LocalAlloc(LMEM_ZEROINIT, (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
	if (!lpDisplayBuf)
	{
		LocalFree(lpMsgBuf);
		return;
	}

	StringCchPrintfW(lpDisplayBuf, LocalSize(lpDisplayBuf) / sizeof(TCHAR), TEXT("%s failed with error %d: %s"), lpszFunction, dw, (void*)lpMsgBuf);
	MessageBoxW(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
#ifdef _DIST
	ExitProcess(dw);
#endif
}

namespace WLD
{
	WinWindow::WinWindow(const WindowProps& props)
		: m_HWND(nullptr), m_Context(nullptr)
	{
		this->WinWindow::Init(props);
	}

	WinWindow::~WinWindow()
	{
		this->WinWindow::Shutdown();
	}

	void WinWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		m_WindowEvent = CreateMemory(WinEvent);
		s_WindowEvent = &m_WindowEvent;

		size_t outSize;
		m_Data.TitleC = CreateArray(char, wcslen(props.Title) + 1);
		wcstombs_s(&outSize, m_Data.TitleC, wcslen(props.Title) + 1, props.Title, wcslen(props.Title));
		
		WLD_CORE_INFO("Creating window {0} ({1}, {2})", m_Data.TitleC, props.Width, props.Height);

		if (!m_HWND)
		{
			m_WindowClass = { sizeof(WNDCLASSEXW), CS_HREDRAW | CS_VREDRAW | CS_OWNDC, WinProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, props.Title, NULL };

			if (!m_WindowClass.hInstance)
			{
				ErrorExit((LPTSTR)TEXT("GetModuleHandle"));
				WLD_CORE_FATAL("Failed to get HINSTANCE!");
			}

			RegisterClassExW(&m_WindowClass);
			m_HWND = CreateWindowExW
			(
				0,                              // Optional window styles.
				m_WindowClass.lpszClassName,    // Window class
				L"Wulled",						// Window text
				WS_OVERLAPPEDWINDOW,            // Window style

				// Size and position
				CW_USEDEFAULT, CW_USEDEFAULT,
				props.Width, props.Height,

				NULL,						// Parent window    
				NULL,						// Menu
				m_WindowClass.hInstance,	// Instance handle
				NULL						// Additional application data
			);
			
			if (!m_HWND)
			{
				ErrorExit((LPTSTR)TEXT("CreateWindowEx"));
				WLD_CORE_FATAL("Failed to create window!");
			}
		}

		m_Context = Graphics::GraphicsContext::createGraphicsContext(&m_HWND, props);
		m_Context->CreateDevice();
		m_Context->MakeCurrent();
		m_Context->Info();
		
		::ShowWindow(m_HWND, SW_SHOWDEFAULT);
		::UpdateWindow(m_HWND);

		SetVSync(true);

		m_WindowEvent->SetWindowSizeCallback([&](HWND window, int width, int height)
		{
			WindowResizeEvent event(width, height);
			m_Data.EventCallback(event);
		});

		m_WindowEvent->SetWindowCloseCallback([&](HWND window)
		{
			WindowCloseEvent event;
			m_Data.EventCallback(event);
		});

		m_WindowEvent->SetKeyCallback([&](HWND window, int key, int scancode, int action, int mods)
		{
			static uint32_t repeat = 0;

			switch (action)
			{
			case WLD_RELEASE:
			{
				KeyReleasedEvent event(key);
				m_Data.EventCallback(event);
				repeat = 0;
				break;
			}
			case WLD_PRESS:
			{
				KeyPressedEvent event(key, repeat);
				m_Data.EventCallback(event);
				repeat++;
				break;
			}
			}
		});

//		m_WindowEvent->SetCharCallback([&](HWND window, uint32_t character)
//		{
//			KeyTypedEvent event(character);
//			m_Data.EventCallback(event);
//		});

		m_WindowEvent->SetMouseButtonCallback([&](HWND window, int button, int action, int mods)
		{
			static uint32_t repeat = 0;

			switch (action)
			{
			case WLD_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				m_Data.EventCallback(event);
				repeat = 0;
				break;
			}
			case WLD_PRESS:
			{
				MouseButtonPressedEvent event(button, repeat);
				m_Data.EventCallback(event);
				repeat++;
				break;
			}
			}
		});

		m_WindowEvent->SetScrollCallback([&](HWND window, double xoffset, double yoffset)
		{
			MouseScrolledEvent event(static_cast<float>(xoffset), static_cast<float>(yoffset));
			m_Data.EventCallback(event);
		});

		
		m_WindowEvent->setCursorPosCallback([&](HWND window, int xpos, int ypos)
		{
			MouseMovedEvent event(static_cast<float>(xpos), static_cast<float>(ypos));
			m_Data.EventCallback(event);
		});
	}

	void WinWindow::Shutdown()
	{
		::DestroyWindow(m_HWND);
		::UnregisterClassW(m_WindowClass.lpszClassName, m_WindowClass.hInstance);
		m_Context = DestroyMemory(m_Context);
		m_WindowEvent = DestroyMemory(m_WindowEvent);
		s_WindowEvent = nullptr;
		m_Data.TitleC = DestroyMemory(m_Data.TitleC);
	}

	void WinWindow::OnUpdate()
	{
		MSG msg;
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		m_Context->SwapBuffers();
		WLD::Graphics::Renderer::RenderCommand::Clear();
	}

	void WinWindow::SetVSync(bool enabled)
	{
		m_Data.VSync = enabled;
	}

	bool WinWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	LRESULT WinWindow::WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		return (**s_WindowEvent).callEvent(hwnd, uMsg, wParam, lParam);
	}
}