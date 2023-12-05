#pragma once

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

const short inline WLDMouseToVKMouse(short mouseButton)
{
	switch (mouseButton)
	{
	case WLD_MOUSE_BUTTON_1: return VK_LBUTTON ;
	case WLD_MOUSE_BUTTON_2: return VK_RBUTTON ;
	case WLD_MOUSE_BUTTON_3: return VK_MBUTTON ;
	case WLD_MOUSE_BUTTON_4: return VK_XBUTTON1;
	case WLD_MOUSE_BUTTON_5: return VK_XBUTTON2;
	default                : return NULL       ;
	}
}

const short inline VKMouseToWLDMouse(short mouseButton)
{
	switch (mouseButton)
	{
	case VK_LBUTTON : return WLD_MOUSE_BUTTON_1;
	case VK_RBUTTON : return WLD_MOUSE_BUTTON_2;
	case VK_MBUTTON : return WLD_MOUSE_BUTTON_3;
	case VK_XBUTTON1: return WLD_MOUSE_BUTTON_4;
	case VK_XBUTTON2: return WLD_MOUSE_BUTTON_5;
	default         : return NULL              ;
	}
}