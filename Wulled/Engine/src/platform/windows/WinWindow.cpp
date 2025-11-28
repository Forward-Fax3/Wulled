#include "wldpch.h"
#include "WLDMem.h"
#include "WinWindow.h"
#include "Renderer.h"
#include "RendererAPI.h"

#include "Log.h"
#include "EngineCore.h"

#include "Event.h"
#include "ApplicationEvent.h"
#include "KeyEvent.h"
#include "MouseEvent.h"
#include "application.h"
#include "WinEvent.h"

#include "KeyCodes.h"
#include "MouseButtonCodes.h"

#include <future>
#include <sstream>
#include <thread>

#include <SDL.h>


//void ErrorExit(LPTSTR lpszFunction)
//{
//	// Retrieve the system error message for the last-error code
//
//	LPVOID lpMsgBuf = NULL;
//	DWORD dw = GetLastError();
//
//	FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dw, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
//
//	// Display the error message and exit the process
//
//	LPTSTR lpDisplayBuf = (LPTSTR)LocalAlloc(LMEM_ZEROINIT, (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
//	if (!lpDisplayBuf)
//	{
//		LocalFree(lpMsgBuf);
//		return;
//	}
//
//	StringCchPrintfW(lpDisplayBuf, LocalSize(lpDisplayBuf) / sizeof(TCHAR), TEXT("%s failed with error %d: %s"), lpszFunction, dw, (void*)lpMsgBuf);
//	MessageBoxW(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);
//
//	LocalFree(lpMsgBuf);
//	LocalFree(lpDisplayBuf);
//#ifdef _DIST
//	ExitProcess(dw);
//#endif
//}

namespace WLD
{
	WinWindow::WinWindow(WindowProps& props)
		: m_Context(nullptr), m_Data(props)
	{
		this->WinWindow::Init();
	}

	WinWindow::~WinWindow()
	{
		this->WinWindow::Shutdown();
	}

	void WinWindow::Init()
	{
		LOG_CORE_INFO("Creating window {0} ({1}, {2})", m_Data.props.TitleC, m_Data.props.Width, m_Data.props.Height);

		m_Context = GraphicsContext::createGraphicsContext(m_Data.props);
		//
		// TODO: Add close if invalid Context
		//
		

		WLD_SDLCheckError(SDL_Init(SDL_INIT_VIDEO));

#if defined linux && SDL_VERSION_ATLEAST(2, 0, 8)
		// Disable compositor bypass
		if (!SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0"))
		{
			std::cout << "SDL can not disable compositor bypass!" << std::endl;
			return 0;
		}
#endif

		// Create window
		m_Data.props.SDLWindow = SDL_CreateWindow(m_Data.props.TitleC, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_Data.props.Width, m_Data.props.Height, m_Data.props.Flags);
		WLD_SDLCheckError(m_Data.props.SDLWindow);

		m_Context->CreateDevice();
		m_Context->MakeCurrent();
		m_Context->Info();

		SetVSync(true);
		
		// Set events
		m_CallEventSet = CreateMemory(WinEvent, m_Data.props.SDLWindow, m_Data.EventCallback);
	}

	void WinWindow::Shutdown()
	{
		ClearEventQueue();
		m_Context->Shutdown();
		DestroyMemory(m_Context);
		SDL_DestroyWindow(m_Data.props.SDLWindow);
		m_Data.props.SDLWindow = nullptr;
		SDL_Quit();

		const char* SDLError = SDL_GetError();
		while (*SDLError)
		{
			LOG_CORE_ERROR("SDL Error: {0}", SDLError);
			SDLError = SDL_GetError();
		}

		DestroyMemory(m_CallEventSet);
	}

	void WinWindow::OnUpdate()
	{
		if (m_SDLWindowNeedsResize)
		{
			WindowResize();
			m_SDLWindowNeedsResize = false;
		}

		ClearEventQueue();
		CheckEvents();

		m_Context->SwapBuffers();
		WLD::RenderCommand::Clear();
	}

	void WinWindow::SetVSync(bool enabled)
	{
		m_Data.VSync = enabled;
		m_Context->SetVsync(m_Data.VSync);
	}

	bool WinWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void WinWindow::OnWindowResize(uint32_t width, uint32_t height)
	{
		m_Data.props.Width = width;
		m_Data.props.Height = height;
		m_SDLWindowNeedsResize = true;
	}

	void WinWindow::WindowResize() const
	{
		m_Context->OnWindowResize();
	}

	void WinWindow::ClearEventQueue()
	{
		for (auto& event : m_IssuedEvents)
		{
			while (!event->isFinished)
				std::this_thread::sleep_for(std::chrono::nanoseconds(50));
			DestroyMemory(event);
		}
		m_IssuedEvents.clear();
	}

	void WinWindow::CheckEvents()
	{
		auto eventCall = [](void* data)
			{
				auto& e = *static_cast<EventData*>(data);
				e.callEvent();
				e.isFinished = true;
				return;
			};
		EventData* e = CreateMemory(EventData, CreateMemory(SDL_Event));
		while (SDL_PollEvent(e->event))
		{
			Application::Get().PushAsyncFunction(eventCall, static_cast<void*>(e));
			m_IssuedEvents.push_back(e);
			e = CreateMemory(EventData, CreateMemory(SDL_Event));
		}
		DestroyMemory(e);
	}

	void EventData::callEvent() const
	{
		WinWindow& window = dynamic_cast<WinWindow&>(Application::Get().GetWindow());
		window.m_CallEventSet->CallEvent(event);
	}
}
