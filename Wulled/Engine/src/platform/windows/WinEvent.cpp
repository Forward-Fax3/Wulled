#include "WLDPCH.h"
#include "WinEvent.h"
#include "KeyCodes.h"
#include "MouseButtonCodes.h"
#include "backends/imgui_impl_sdl2.h"
#include <SDL.h>
#include <SDL_thread.h>

#include "ApplicationEvent.h"
#include "KeyEvent.h"
#include "MouseEvent.h"


namespace WLD
{
	WinEvent::WinEvent(SDL_Window* mainWindow, Window::EventCallbackFn& functionCallBack)
		: m_MainWindow(mainWindow), m_EventCallback(functionCallBack)
	{
	}

	WinEvent::~WinEvent()
	{
	}

	bool WinEvent::CallEvent(SDL_Event* SDLEvent)
	{
//		ImGui_ImplSDL2_ProcessEvent(SDLEvent);

		switch (SDLEvent->type)
		{
		case SDL_QUIT:
		{
			CloseWindow();
			return 0;
		}
		case SDL_WINDOWEVENT_RESIZED:
		{
			ResizeWindow((uint32_t)SDLEvent->window.data1, (uint32_t)SDLEvent->window.data2);
			return 0;
		}
		case SDL_KEYDOWN:
		{
			short key = SDLKeyToWLDKey(SDLEvent->key.keysym.sym);
			m_KeyRepeats[key] = m_KeyRepeats.find(key) != m_KeyRepeats.end() ? m_KeyRepeats[key] + 1 : 0;
			KeyPressedEvent event(key, m_KeyRepeats[key]);
			m_EventCallback(event);
			return 0;
		}
		case SDL_KEYUP:
		{
			short key = SDLKeyToWLDKey(SDLEvent->key.keysym.sym);
			KeyReleasedEvent event(key);
			m_EventCallback(event);
			m_KeyRepeats.erase(key);
			return 0;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			short mouseButton = SDLMouseToWLDMouse(SDLEvent->button.button);
			m_MouseRepeats[mouseButton] = m_MouseRepeats.find(mouseButton) != m_MouseRepeats.end() ? m_MouseRepeats[mouseButton] + 1 : 0;
			MouseButtonPressedEvent event(mouseButton, m_MouseRepeats[mouseButton]);
			m_EventCallback(event);
			return 0;
		}
		case SDL_MOUSEBUTTONUP:
		{
			short mouseButton = SDLMouseToWLDMouse(SDLEvent->button.button);
			MouseButtonReleasedEvent event(mouseButton);
			m_EventCallback(event);
			m_MouseRepeats.erase(mouseButton);
			return 0;
		}
		case SDL_MOUSEWHEEL:
		{
			MouseScrolledEvent event((float)SDLEvent->wheel.x, (float)SDLEvent->wheel.y);
			m_EventCallback(event);
			return 0;
		}
		case SDL_MOUSEMOTION:
		{
			int32_t xpos = SDLEvent->motion.x;
			int32_t ypos = SDLEvent->motion.y;

			MouseMovedEvent event(static_cast<float>(xpos), static_cast<float>(ypos));
			m_EventCallback(event);
			return 0;
		}
		case SDL_WINDOWEVENT:
		{
			if (SDLEvent->window.windowID != SDL_GetWindowID(m_MainWindow))
				return 0;

			Uint8 event = SDLEvent->window.event;
			switch (event)
			{
			case SDL_WINDOWEVENT_RESIZED:
				ResizeWindow((uint32_t)SDLEvent->window.data1, (uint32_t)SDLEvent->window.data2);
				break;
			case SDL_WINDOWEVENT_CLOSE:
				CloseWindow();
				break;
			}
			return 0;
		}
		}
		return 0;
	}

	// private
	// helper functions
	void WinEvent::CloseWindow()
	{
		WindowCloseEvent event;
		m_EventCallback(event);
	}

	void WinEvent::ResizeWindow(uint32_t width, uint32_t height)
	{
		WindowResizeEvent event(width, height);
		m_EventCallback(event);
	}
}