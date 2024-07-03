#pragma once
#include <SDL_mouse.h>


// From glfw3.h
#define WLD_MOUSE_BUTTON_1         0
#define WLD_MOUSE_BUTTON_2         1
#define WLD_MOUSE_BUTTON_3         2
#define WLD_MOUSE_BUTTON_4         3
#define WLD_MOUSE_BUTTON_5         4
#define WLD_MOUSE_BUTTON_6         5
#define WLD_MOUSE_BUTTON_7         6
#define WLD_MOUSE_BUTTON_8         7
#define WLD_MOUSE_BUTTON_LAST      WLD_MOUSE_BUTTON_8
#define WLD_MOUSE_BUTTON_LEFT      WLD_MOUSE_BUTTON_1
#define WLD_MOUSE_BUTTON_RIGHT     WLD_MOUSE_BUTTON_2
#define WLD_MOUSE_BUTTON_MIDDLE    WLD_MOUSE_BUTTON_3

const uint32_t inline WLDMouseToSDLMouse(uint32_t mouseButton)
{
	switch (mouseButton)
	{
	case WLD_MOUSE_BUTTON_1: return SDL_BUTTON_LEFT  ;
	case WLD_MOUSE_BUTTON_2: return SDL_BUTTON_RIGHT ;
	case WLD_MOUSE_BUTTON_3: return SDL_BUTTON_MIDDLE;
	case WLD_MOUSE_BUTTON_4: return SDL_BUTTON_X1    ;
	case WLD_MOUSE_BUTTON_5: return SDL_BUTTON_X2    ;
	default                : return NULL             ;
	}
}

const uint32_t inline SDLMouseToWLDMouse(uint32_t mouseButton)
{
	switch (mouseButton)
	{
	case SDL_BUTTON_LEFT  : return WLD_MOUSE_BUTTON_1;
	case SDL_BUTTON_RIGHT : return WLD_MOUSE_BUTTON_2;
	case SDL_BUTTON_MIDDLE: return WLD_MOUSE_BUTTON_3;
	case SDL_BUTTON_X1    : return WLD_MOUSE_BUTTON_4;
	case SDL_BUTTON_X2    : return WLD_MOUSE_BUTTON_5;
	default               : return NULL              ;
	}
}