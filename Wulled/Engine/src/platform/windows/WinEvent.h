#pragma once
#include <map>

#include "Engine/src/core/EngineCore.h"
#include "Engine/src/core/Window.h"
#include "Engine/src/core/Events/windowEvent.h"

#include "SDL_events.h"


namespace WLD
{
	class WLD_API WinEvent : public WinWindowEvent
	{
	public:
		WinEvent(SDL_Window* mainWindow, Window::EventCallbackFn& functionCallBack);
		virtual ~WinEvent() override;

		bool CallEvent(SDL_Event* SDLEvent) override;

	// data
	private:
		SDL_Window* m_MainWindow;
		Window::EventCallbackFn& m_EventCallback;
		std::map<uint32_t, uint32_t> m_KeyRepeats, m_MouseRepeats;

	// helper functions
	private:
		void CloseWindow();
		void ResizeWindow(uint32_t width, uint32_t height);
	};
}