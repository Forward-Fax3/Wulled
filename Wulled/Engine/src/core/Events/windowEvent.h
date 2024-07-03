#pragma once
#include <functional>

#include <SDL_events.h>


namespace WLD
{
	class WLD_API WinWindowEvent
	{
	public:
		virtual ~WinWindowEvent() = default;

		virtual bool CallEvent(SDL_Event* SDLEvent) = 0;
	};
}