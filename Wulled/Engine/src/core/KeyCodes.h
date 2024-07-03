#pragma once
#include <SDL_keycode.h>

// From glfw3.h
#define WLD_KEY_SPACE              32
#define WLD_KEY_APOSTROPHE         39  /* ' */
#define WLD_KEY_COMMA              44  /* , */
#define WLD_KEY_MINUS              45  /* - */
#define WLD_KEY_PERIOD             46  /* . */
#define WLD_KEY_SLASH              47  /* / */
#define WLD_KEY_0                  48
#define WLD_KEY_1                  49
#define WLD_KEY_2                  50
#define WLD_KEY_3                  51
#define WLD_KEY_4                  52
#define WLD_KEY_5                  53
#define WLD_KEY_6                  54
#define WLD_KEY_7                  55
#define WLD_KEY_8                  56
#define WLD_KEY_9                  57
#define WLD_KEY_SEMICOLON          59  /* ; */
#define WLD_KEY_EQUAL              61  /* = */
#define WLD_KEY_A                  65
#define WLD_KEY_B                  66
#define WLD_KEY_C                  67
#define WLD_KEY_D                  68
#define WLD_KEY_E                  69
#define WLD_KEY_F                  70
#define WLD_KEY_G                  71
#define WLD_KEY_H                  72
#define WLD_KEY_I                  73
#define WLD_KEY_J                  74
#define WLD_KEY_K                  75
#define WLD_KEY_L                  76
#define WLD_KEY_M                  77
#define WLD_KEY_N                  78
#define WLD_KEY_O                  79
#define WLD_KEY_P                  80
#define WLD_KEY_Q                  81
#define WLD_KEY_R                  82
#define WLD_KEY_S                  83
#define WLD_KEY_T                  84
#define WLD_KEY_U                  85
#define WLD_KEY_V                  86
#define WLD_KEY_W                  87
#define WLD_KEY_X                  88
#define WLD_KEY_Y                  89
#define WLD_KEY_Z                  90
#define WLD_KEY_LEFT_BRACKET       91  /* [ */
#define WLD_KEY_BACKSLASH          92  /* \ */
#define WLD_KEY_RIGHT_BRACKET      93  /* ] */
#define WLD_KEY_GRAVE_ACCENT       96  /* ` */
#define WLD_KEY_WORLD_1            161 /* non-US #1 */
#define WLD_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define WLD_KEY_ESCAPE             256
#define WLD_KEY_ENTER              257
#define WLD_KEY_TAB                258
#define WLD_KEY_BACKSPACE          259
#define WLD_KEY_INSERT             260
#define WLD_KEY_DELETE             261
#define WLD_KEY_RIGHT              262
#define WLD_KEY_LEFT               263
#define WLD_KEY_DOWN               264
#define WLD_KEY_UP                 265
#define WLD_KEY_PAGE_UP            266
#define WLD_KEY_PAGE_DOWN          267
#define WLD_KEY_HOME               268
#define WLD_KEY_END                269
#define WLD_KEY_CAPS_LOCK          280
#define WLD_KEY_SCROLL_LOCK        281
#define WLD_KEY_NUM_LOCK           282
#define WLD_KEY_PRINT_SCREEN       283
#define WLD_KEY_PAUSE              284
#define WLD_KEY_F1                 290
#define WLD_KEY_F2                 291
#define WLD_KEY_F3                 292
#define WLD_KEY_F4                 293
#define WLD_KEY_F5                 294
#define WLD_KEY_F6                 295
#define WLD_KEY_F7                 296
#define WLD_KEY_F8                 297
#define WLD_KEY_F9                 298
#define WLD_KEY_F10                299
#define WLD_KEY_F11                300
#define WLD_KEY_F12                301
#define WLD_KEY_F13                302
#define WLD_KEY_F14                303
#define WLD_KEY_F15                304
#define WLD_KEY_F16                305
#define WLD_KEY_F17                306
#define WLD_KEY_F18                307
#define WLD_KEY_F19                308
#define WLD_KEY_F20                309
#define WLD_KEY_F21                310
#define WLD_KEY_F22                311
#define WLD_KEY_F23                312
#define WLD_KEY_F24                313
#define WLD_KEY_F25                314
#define WLD_KEY_KP_0               320
#define WLD_KEY_KP_1               321
#define WLD_KEY_KP_2               322
#define WLD_KEY_KP_3               323
#define WLD_KEY_KP_4               324
#define WLD_KEY_KP_5               325
#define WLD_KEY_KP_6               326
#define WLD_KEY_KP_7               327
#define WLD_KEY_KP_8               328
#define WLD_KEY_KP_9               329
#define WLD_KEY_KP_DECIMAL         330
#define WLD_KEY_KP_DIVIDE          331
#define WLD_KEY_KP_MULTIPLY        332
#define WLD_KEY_KP_SUBTRACT        333
#define WLD_KEY_KP_ADD             334
#define WLD_KEY_KP_ENTER           335
#define WLD_KEY_KP_EQUAL           336
#define WLD_KEY_LEFT_SHIFT         340
#define WLD_KEY_LEFT_CONTROL       341
#define WLD_KEY_LEFT_ALT           342
#define WLD_KEY_LEFT_SUPER         343
#define WLD_KEY_RIGHT_SHIFT        344
#define WLD_KEY_RIGHT_CONTROL      345
#define WLD_KEY_RIGHT_ALT          346
#define WLD_KEY_RIGHT_SUPER        347
#define WLD_KEY_MENU               348
#define WLD_RELEASE                0ui8
#define WLD_PRESS                  1ui8


const uint32_t inline WLDKeyToSDLKey(uint32_t key)
{
	switch (key)
	{
	case WLD_KEY_BACKSPACE    : return SDLK_BACKSPACE    ;
	case WLD_KEY_TAB          : return SDLK_TAB          ;
	case WLD_KEY_ENTER        : return SDLK_RETURN       ;
	case WLD_KEY_PAUSE        : return SDLK_PAUSE        ;
	case WLD_KEY_CAPS_LOCK    : return KMOD_CAPS         ;
	case WLD_KEY_ESCAPE       : return SDLK_ESCAPE       ;
	case WLD_KEY_SPACE        : return SDLK_KP_SPACE     ;
	case WLD_KEY_PAGE_UP      : return SDLK_PAGEUP       ;
	case WLD_KEY_PAGE_DOWN    : return SDLK_PAGEDOWN     ;
	case WLD_KEY_END          : return SDLK_END          ;
	case WLD_KEY_HOME         : return SDLK_HOME         ;
	case WLD_KEY_LEFT         : return SDLK_LEFT         ;
	case WLD_KEY_UP           : return SDLK_UP           ;
	case WLD_KEY_RIGHT        : return SDLK_RIGHT        ;
	case WLD_KEY_DOWN         : return SDLK_DOWN         ;
	case WLD_KEY_PRINT_SCREEN : return SDLK_PRINTSCREEN  ;
	case WLD_KEY_INSERT       : return SDLK_INSERT       ;
	case WLD_KEY_DELETE       : return SDLK_DELETE       ;
	case WLD_KEY_0            : return SDLK_0            ;
	case WLD_KEY_1            : return SDLK_1            ;
	case WLD_KEY_2            : return SDLK_2            ;
	case WLD_KEY_3            : return SDLK_3            ;
	case WLD_KEY_4            : return SDLK_4            ;
	case WLD_KEY_5            : return SDLK_5            ;
	case WLD_KEY_6            : return SDLK_6            ;
	case WLD_KEY_7            : return SDLK_7            ;
	case WLD_KEY_8            : return SDLK_8            ;
	case WLD_KEY_9            : return SDLK_9            ;
	case WLD_KEY_A            : return SDLK_a            ;
	case WLD_KEY_B            : return SDLK_b            ;
	case WLD_KEY_C            : return SDLK_c            ;
	case WLD_KEY_D            : return SDLK_d            ;
	case WLD_KEY_E            : return SDLK_e            ;
	case WLD_KEY_F            : return SDLK_f            ;
	case WLD_KEY_G            : return SDLK_g            ;
	case WLD_KEY_H            : return SDLK_h            ;
	case WLD_KEY_I            : return SDLK_i            ;
	case WLD_KEY_J            : return SDLK_j            ;
	case WLD_KEY_K            : return SDLK_k            ;
	case WLD_KEY_L            : return SDLK_l            ;
	case WLD_KEY_M            : return SDLK_m            ;
	case WLD_KEY_N            : return SDLK_n            ;
	case WLD_KEY_O            : return SDLK_o            ;
	case WLD_KEY_P            : return SDLK_p            ;
	case WLD_KEY_Q            : return SDLK_q            ;
	case WLD_KEY_R            : return SDLK_r            ;
	case WLD_KEY_S            : return SDLK_s            ;
	case WLD_KEY_T            : return SDLK_t            ;
	case WLD_KEY_U            : return SDLK_u            ;
	case WLD_KEY_V            : return SDLK_v            ;
	case WLD_KEY_W            : return SDLK_w            ;
	case WLD_KEY_X            : return SDLK_x            ;
	case WLD_KEY_Y            : return SDLK_y            ;
	case WLD_KEY_Z            : return SDLK_z            ;
	case WLD_KEY_LEFT_BRACKET : return SDLK_KP_LEFTBRACE ;
	case WLD_KEY_BACKSLASH    : return SDLK_BACKSLASH    ;
	case WLD_KEY_RIGHT_BRACKET: return SDLK_KP_RIGHTBRACE;
//	case WLD_KEY_GRAVE_ACCENT : return VK_OEM_3          ;
//	case WLD_KEY_WORLD_1      : return VK_OEM_102        ;
//	case WLD_KEY_WORLD_2      : return VK_OEM_8          ;
	case WLD_KEY_KP_0         : return SDLK_KP_0         ;
	case WLD_KEY_KP_1         : return SDLK_KP_1         ;
	case WLD_KEY_KP_2         : return SDLK_KP_2         ;
	case WLD_KEY_KP_3         : return SDLK_KP_3         ;
	case WLD_KEY_KP_4         : return SDLK_KP_4         ;
	case WLD_KEY_KP_5         : return SDLK_KP_5         ;
	case WLD_KEY_KP_6         : return SDLK_KP_6         ;
	case WLD_KEY_KP_7         : return SDLK_KP_7         ;
	case WLD_KEY_KP_8         : return SDLK_KP_8         ;
	case WLD_KEY_KP_9         : return SDLK_KP_9         ;
	case WLD_KEY_KP_DECIMAL   : return SDLK_KP_DECIMAL   ;
	case WLD_KEY_KP_DIVIDE    : return SDLK_KP_DIVIDE    ;
	case WLD_KEY_KP_MULTIPLY  : return SDLK_KP_MULTIPLY  ;
	case WLD_KEY_KP_SUBTRACT  : return SDLK_MINUS        ;
	case WLD_KEY_KP_ADD       : return SDLK_PLUS         ;
	case WLD_KEY_KP_ENTER     : return SDLK_KP_ENTER     ;
	case WLD_KEY_KP_EQUAL     : return SDLK_KP_EQUALS    ;
	case WLD_KEY_LEFT_SHIFT   : return KMOD_LSHIFT       ;
	case WLD_KEY_LEFT_CONTROL : return KMOD_LCTRL        ;
	case WLD_KEY_LEFT_ALT     : return KMOD_LALT         ;
	case WLD_KEY_LEFT_SUPER   : return KMOD_LGUI         ;
	case WLD_KEY_RIGHT_SHIFT  : return KMOD_RSHIFT       ;
	case WLD_KEY_RIGHT_CONTROL: return KMOD_RCTRL        ;
	case WLD_KEY_RIGHT_ALT    : return KMOD_RALT         ;
	case WLD_KEY_RIGHT_SUPER  : return KMOD_RGUI         ;
	case WLD_KEY_MENU         : return SDLK_MENU         ;
	case WLD_KEY_F1           : return SDLK_F1           ;
	case WLD_KEY_F2           : return SDLK_F2           ;
	case WLD_KEY_F3           : return SDLK_F3           ;
	case WLD_KEY_F4           : return SDLK_F4           ;
	case WLD_KEY_F5           : return SDLK_F5           ;
	case WLD_KEY_F6           : return SDLK_F6           ;
	case WLD_KEY_F7           : return SDLK_F7           ;
	case WLD_KEY_F8           : return SDLK_F8           ;
	case WLD_KEY_F9           : return SDLK_F9           ;
	case WLD_KEY_F10          : return SDLK_F10          ;
	case WLD_KEY_F11          : return SDLK_F11          ;
	case WLD_KEY_F12          : return SDLK_F12          ;
	case WLD_KEY_F13          : return SDLK_F13          ;
	case WLD_KEY_F14          : return SDLK_F14          ;
	case WLD_KEY_F15          : return SDLK_F15          ;
	case WLD_KEY_F16          : return SDLK_F16          ;
	case WLD_KEY_F17          : return SDLK_F17          ;
	case WLD_KEY_F18          : return SDLK_F18          ;
	case WLD_KEY_F19          : return SDLK_F19          ;
	case WLD_KEY_F20          : return SDLK_F20          ;
	case WLD_KEY_F21          : return SDLK_F21          ;
	case WLD_KEY_F22          : return SDLK_F22          ;
	case WLD_KEY_F23          : return SDLK_F23          ;
	case WLD_KEY_F24          : return SDLK_F24          ;
	default                   : return NULL              ;
	}
}

const uint32_t inline SDLKeyToWLDKey(uint32_t key)
{
	switch (key)
	{
	case SDLK_BACKSPACE    : return WLD_KEY_BACKSPACE    ;
	case SDLK_TAB          : return WLD_KEY_TAB          ;
	case SDLK_RETURN       : return WLD_KEY_ENTER        ;
	case SDLK_PAUSE        : return WLD_KEY_PAUSE        ;
	case KMOD_CAPS         : return WLD_KEY_CAPS_LOCK    ;
	case SDLK_ESCAPE       : return WLD_KEY_ESCAPE       ;
	case SDLK_KP_SPACE     : return WLD_KEY_SPACE        ;
	case SDLK_PAGEUP       : return WLD_KEY_PAGE_UP      ;
	case SDLK_PAGEDOWN     : return WLD_KEY_PAGE_DOWN    ;
	case SDLK_END          : return WLD_KEY_END          ;
	case SDLK_HOME         : return WLD_KEY_HOME         ;
	case SDLK_LEFT         : return WLD_KEY_LEFT         ;
	case SDLK_UP           : return WLD_KEY_UP           ;
	case SDLK_RIGHT        : return WLD_KEY_RIGHT        ;
	case SDLK_DOWN         : return WLD_KEY_DOWN         ;
	case SDLK_PRINTSCREEN  : return WLD_KEY_PRINT_SCREEN ;
	case SDLK_INSERT       : return WLD_KEY_INSERT       ;
	case SDLK_DELETE       : return WLD_KEY_DELETE       ;
	case SDLK_0            : return WLD_KEY_0            ;
	case SDLK_1            : return WLD_KEY_1            ;
	case SDLK_2            : return WLD_KEY_2            ;
	case SDLK_3            : return WLD_KEY_3            ;
	case SDLK_4            : return WLD_KEY_4            ;
	case SDLK_5            : return WLD_KEY_5            ;
	case SDLK_6            : return WLD_KEY_6            ;
	case SDLK_7            : return WLD_KEY_7            ;
	case SDLK_8            : return WLD_KEY_8            ;
	case SDLK_9            : return WLD_KEY_9            ;
	case SDLK_a            : return WLD_KEY_A            ;
	case SDLK_b            : return WLD_KEY_B            ;
	case SDLK_c            : return WLD_KEY_C            ;
	case SDLK_d            : return WLD_KEY_D            ;
	case SDLK_e            : return WLD_KEY_E            ;
	case SDLK_f            : return WLD_KEY_F            ;
	case SDLK_g            : return WLD_KEY_G            ;
	case SDLK_h            : return WLD_KEY_H            ;
	case SDLK_i            : return WLD_KEY_I            ;
	case SDLK_j            : return WLD_KEY_J            ;
	case SDLK_k            : return WLD_KEY_K            ;
	case SDLK_l            : return WLD_KEY_L            ;
	case SDLK_m            : return WLD_KEY_M            ;
	case SDLK_n            : return WLD_KEY_N            ;
	case SDLK_o            : return WLD_KEY_O            ;
	case SDLK_p            : return WLD_KEY_P            ;
	case SDLK_q            : return WLD_KEY_Q            ;
	case SDLK_r            : return WLD_KEY_R            ;
	case SDLK_s            : return WLD_KEY_S            ;
	case SDLK_t            : return WLD_KEY_T            ;
	case SDLK_u            : return WLD_KEY_U            ;
	case SDLK_v            : return WLD_KEY_V            ;
	case SDLK_w            : return WLD_KEY_W            ;
	case SDLK_x            : return WLD_KEY_X            ;
	case SDLK_y            : return WLD_KEY_Y            ;
	case SDLK_z            : return WLD_KEY_Z            ;
	case SDLK_KP_LEFTBRACE : return WLD_KEY_LEFT_BRACKET ;
	case SDLK_BACKSLASH    : return WLD_KEY_BACKSLASH    ;
	case SDLK_KP_RIGHTBRACE: return WLD_KEY_RIGHT_BRACKET;
//	case VK_OEM_3          : return WLD_KEY_GRAVE_ACCENT ;
//	case VK_OEM_102        : return WLD_KEY_WORLD_1      ;
//	case VK_OEM_8          : return WLD_KEY_WORLD_2      ;
	case SDLK_KP_0         : return WLD_KEY_KP_0         ;
	case SDLK_KP_1         : return WLD_KEY_KP_1         ;
	case SDLK_KP_2         : return WLD_KEY_KP_2         ;
	case SDLK_KP_3         : return WLD_KEY_KP_3         ;
	case SDLK_KP_4         : return WLD_KEY_KP_4         ;
	case SDLK_KP_5         : return WLD_KEY_KP_5         ;
	case SDLK_KP_6         : return WLD_KEY_KP_6         ;
	case SDLK_KP_7         : return WLD_KEY_KP_7         ;
	case SDLK_KP_8         : return WLD_KEY_KP_8         ;
	case SDLK_KP_9         : return WLD_KEY_KP_9         ;
	case SDLK_KP_DECIMAL   : return WLD_KEY_KP_DECIMAL   ;
	case SDLK_KP_DIVIDE    : return WLD_KEY_KP_DIVIDE    ;
	case SDLK_KP_MULTIPLY  : return WLD_KEY_KP_MULTIPLY  ;
	case SDLK_MINUS        : return WLD_KEY_KP_SUBTRACT  ;
	case SDLK_PLUS         : return WLD_KEY_KP_ADD       ;
	case SDLK_KP_ENTER     : return WLD_KEY_KP_ENTER     ;
	case SDLK_KP_EQUALS    : return WLD_KEY_KP_EQUAL     ;
	case KMOD_LSHIFT       : return WLD_KEY_LEFT_SHIFT   ;
	case KMOD_LCTRL        : return WLD_KEY_LEFT_CONTROL ;
	case KMOD_LALT         : return WLD_KEY_LEFT_ALT     ;
	case KMOD_LGUI         : return WLD_KEY_LEFT_SUPER   ;
	case KMOD_RSHIFT       : return WLD_KEY_RIGHT_SHIFT  ;
	case KMOD_RCTRL        : return WLD_KEY_RIGHT_CONTROL;
	case KMOD_RALT         : return WLD_KEY_RIGHT_ALT    ;
	case KMOD_RGUI         : return WLD_KEY_RIGHT_SUPER  ;
	case SDLK_MENU         : return WLD_KEY_MENU         ;
	case SDLK_F1           : return WLD_KEY_F1           ;
	case SDLK_F2           : return WLD_KEY_F2           ;
	case SDLK_F3           : return WLD_KEY_F3           ;
	case SDLK_F4           : return WLD_KEY_F4           ;
	case SDLK_F5           : return WLD_KEY_F5           ;
	case SDLK_F6           : return WLD_KEY_F6           ;
	case SDLK_F7           : return WLD_KEY_F7           ;
	case SDLK_F8           : return WLD_KEY_F8           ;
	case SDLK_F9           : return WLD_KEY_F9           ;
	case SDLK_F10          : return WLD_KEY_F10          ;
	case SDLK_F11          : return WLD_KEY_F11          ;
	case SDLK_F12          : return WLD_KEY_F12          ;
	case SDLK_F13          : return WLD_KEY_F13          ;
	case SDLK_F14          : return WLD_KEY_F14          ;
	case SDLK_F15          : return WLD_KEY_F15          ;
	case SDLK_F16          : return WLD_KEY_F16          ;
	case SDLK_F17          : return WLD_KEY_F17          ;
	case SDLK_F18          : return WLD_KEY_F18          ;
	case SDLK_F19          : return WLD_KEY_F19          ;
	case SDLK_F20          : return WLD_KEY_F20          ;
	case SDLK_F21          : return WLD_KEY_F21          ;
	case SDLK_F22          : return WLD_KEY_F22          ;
	case SDLK_F23          : return WLD_KEY_F23          ;
	case SDLK_F24          : return WLD_KEY_F24          ;
	default                : return NULL                 ;
	}
}

