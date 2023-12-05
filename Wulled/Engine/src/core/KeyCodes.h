#pragma once

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
#define WLD_RELEASE                0
#define WLD_PRESS                  1


const short inline WLDKeyToVKey(short key)
{
	switch (key)
	{
	case WLD_KEY_BACKSPACE    : return VK_BACK         ;
	case WLD_KEY_TAB          : return VK_TAB          ;
	case WLD_KEY_ENTER        : return VK_RETURN       ;
	case WLD_KEY_PAUSE        : return VK_PAUSE        ;
	case WLD_KEY_CAPS_LOCK    : return VK_CAPITAL      ;
	case WLD_KEY_ESCAPE       : return VK_ESCAPE       ;
	case WLD_KEY_SPACE        : return VK_SPACE        ;
	case WLD_KEY_PAGE_UP      : return VK_PRIOR        ;
	case WLD_KEY_PAGE_DOWN    : return VK_NEXT         ;
	case WLD_KEY_END          : return VK_END          ;
	case WLD_KEY_HOME         : return VK_HOME         ;
	case WLD_KEY_LEFT         : return VK_LEFT         ;
	case WLD_KEY_UP           : return VK_UP           ;
	case WLD_KEY_RIGHT        : return VK_RIGHT        ;
	case WLD_KEY_DOWN         : return VK_DOWN         ;
	case WLD_KEY_PRINT_SCREEN : return VK_SNAPSHOT     ;
	case WLD_KEY_INSERT       : return VK_INSERT       ;
	case WLD_KEY_DELETE       : return VK_DELETE       ;
	case WLD_KEY_0            : return 0x30            ;
	case WLD_KEY_1            : return 0x31            ;
	case WLD_KEY_2            : return 0x32            ;
	case WLD_KEY_3            : return 0x33            ;
	case WLD_KEY_4            : return 0x34            ;
	case WLD_KEY_5            : return 0x35            ;
	case WLD_KEY_6            : return 0x36            ;
	case WLD_KEY_7            : return 0x37            ;
	case WLD_KEY_8            : return 0x38            ;
	case WLD_KEY_9            : return 0x39            ;
	case WLD_KEY_A            : return 0x41            ;
	case WLD_KEY_B            : return 0x42            ;
	case WLD_KEY_C            : return 0x43            ;
	case WLD_KEY_D            : return 0x44            ;
	case WLD_KEY_E            : return 0x45            ;
	case WLD_KEY_F            : return 0x46            ;
	case WLD_KEY_G            : return 0x47            ;
	case WLD_KEY_H            : return 0x48            ;
	case WLD_KEY_I            : return 0x49            ;
	case WLD_KEY_J            : return 0x4A            ;
	case WLD_KEY_K            : return 0x4B            ;
	case WLD_KEY_L            : return 0x4C            ;
	case WLD_KEY_M            : return 0x4D            ;
	case WLD_KEY_N            : return 0x4E            ;
	case WLD_KEY_O            : return 0x4F            ;
	case WLD_KEY_P            : return 0x50            ;
	case WLD_KEY_Q            : return 0x51            ;
	case WLD_KEY_R            : return 0x52            ;
	case WLD_KEY_S            : return 0x53            ;
	case WLD_KEY_T            : return 0x54            ;
	case WLD_KEY_U            : return 0x55            ;
	case WLD_KEY_V            : return 0x56            ;
	case WLD_KEY_W            : return 0x57            ;
	case WLD_KEY_X            : return 0x58            ;
	case WLD_KEY_Y            : return 0x59            ;
	case WLD_KEY_Z            : return 0x5A            ;
	case WLD_KEY_LEFT_BRACKET : return VK_OEM_4        ;
	case WLD_KEY_BACKSLASH    : return VK_OEM_5        ;
	case WLD_KEY_RIGHT_BRACKET: return VK_OEM_6        ;
	case WLD_KEY_GRAVE_ACCENT : return VK_OEM_3        ;
	case WLD_KEY_WORLD_1      : return VK_OEM_102      ;
	case WLD_KEY_WORLD_2      : return VK_OEM_8        ;
	case WLD_KEY_KP_0         : return VK_NUMPAD0      ;
	case WLD_KEY_KP_1         : return VK_NUMPAD1      ;
	case WLD_KEY_KP_2         : return VK_NUMPAD2      ;
	case WLD_KEY_KP_3         : return VK_NUMPAD3      ;
	case WLD_KEY_KP_4         : return VK_NUMPAD4      ;
	case WLD_KEY_KP_5         : return VK_NUMPAD5      ;
	case WLD_KEY_KP_6         : return VK_NUMPAD6      ;
	case WLD_KEY_KP_7         : return VK_NUMPAD7      ;
	case WLD_KEY_KP_8         : return VK_NUMPAD8      ;
	case WLD_KEY_KP_9         : return VK_NUMPAD9      ;
	case WLD_KEY_KP_DECIMAL   : return VK_DECIMAL      ;
	case WLD_KEY_KP_DIVIDE    : return VK_DIVIDE       ;
	case WLD_KEY_KP_MULTIPLY  : return VK_MULTIPLY     ;
	case WLD_KEY_KP_SUBTRACT  : return VK_SUBTRACT     ;
	case WLD_KEY_KP_ADD       : return VK_ADD          ;
	case WLD_KEY_KP_ENTER     : return VK_RETURN       ;
	case WLD_KEY_KP_EQUAL     : return VK_OEM_NEC_EQUAL;
	case WLD_KEY_LEFT_SHIFT   : return VK_LSHIFT       ;
	case WLD_KEY_LEFT_CONTROL : return VK_LCONTROL     ;
	case WLD_KEY_LEFT_ALT     : return VK_LMENU        ;
	case WLD_KEY_LEFT_SUPER   : return VK_LWIN         ;
	case WLD_KEY_RIGHT_SHIFT  : return VK_RSHIFT       ;
	case WLD_KEY_RIGHT_CONTROL: return VK_RCONTROL     ;
	case WLD_KEY_RIGHT_ALT    : return VK_RMENU        ;
	case WLD_KEY_RIGHT_SUPER  : return VK_RWIN         ;
	case WLD_KEY_MENU         : return VK_APPS         ;
	case WLD_KEY_F1           : return VK_F1           ;
	case WLD_KEY_F2           : return VK_F2           ;
	case WLD_KEY_F3           : return VK_F3           ;
	case WLD_KEY_F4           : return VK_F4           ;
	case WLD_KEY_F5           : return VK_F5           ;
	case WLD_KEY_F6           : return VK_F6           ;
	case WLD_KEY_F7           : return VK_F7           ;
	case WLD_KEY_F8           : return VK_F8           ;
	case WLD_KEY_F9           : return VK_F9           ;
	case WLD_KEY_F10          : return VK_F10          ;
	case WLD_KEY_F11          : return VK_F11          ;
	case WLD_KEY_F12          : return VK_F12          ;
	case WLD_KEY_F13          : return VK_F13          ;
	case WLD_KEY_F14          : return VK_F14          ;
	case WLD_KEY_F15          : return VK_F15          ;
	case WLD_KEY_F16          : return VK_F16          ;
	case WLD_KEY_F17          : return VK_F17          ;
	case WLD_KEY_F18          : return VK_F18          ;
	case WLD_KEY_F19          : return VK_F19          ;
	case WLD_KEY_F20          : return VK_F20          ;
	case WLD_KEY_F21          : return VK_F21          ;
	case WLD_KEY_F22          : return VK_F22          ;
	case WLD_KEY_F23          : return VK_F23          ;
	case WLD_KEY_F24          : return VK_F24          ;
	default                   : return NULL            ;
	}
}

const short inline VKeyToWLDKey(short key)
{
	switch (key)
	{
	case VK_BACK         : return WLD_KEY_BACKSPACE    ;
	case VK_TAB          : return WLD_KEY_TAB          ;
	case VK_RETURN       : return WLD_KEY_ENTER        ;
	case VK_PAUSE        : return WLD_KEY_PAUSE        ;
	case VK_CAPITAL      : return WLD_KEY_CAPS_LOCK    ;
	case VK_ESCAPE       : return WLD_KEY_ESCAPE       ;
	case VK_SPACE        : return WLD_KEY_SPACE        ;
	case VK_PRIOR        : return WLD_KEY_PAGE_UP      ;
	case VK_NEXT         : return WLD_KEY_PAGE_DOWN    ;
	case VK_END          : return WLD_KEY_END          ;
	case VK_HOME         : return WLD_KEY_HOME         ;
	case VK_LEFT         : return WLD_KEY_LEFT         ;
	case VK_UP           : return WLD_KEY_UP           ;
	case VK_RIGHT        : return WLD_KEY_RIGHT        ;
	case VK_DOWN         : return WLD_KEY_DOWN         ;
	case VK_SNAPSHOT     : return WLD_KEY_PRINT_SCREEN ;
	case VK_INSERT       : return WLD_KEY_INSERT       ;
	case VK_DELETE       : return WLD_KEY_DELETE       ;
	case 0x30            : return WLD_KEY_0            ;
	case 0x31            : return WLD_KEY_1            ;
	case 0x32            : return WLD_KEY_2            ;
	case 0x33            : return WLD_KEY_3            ;
	case 0x34            : return WLD_KEY_4            ;
	case 0x35            : return WLD_KEY_5            ;
	case 0x36            : return WLD_KEY_6            ;
	case 0x37            : return WLD_KEY_7            ;
	case 0x38            : return WLD_KEY_8            ;
	case 0x39            : return WLD_KEY_9            ;
	case 0x41            : return WLD_KEY_A            ;
	case 0x42            : return WLD_KEY_B            ;
	case 0x43            : return WLD_KEY_C            ;
	case 0x44            : return WLD_KEY_D            ;
	case 0x45            : return WLD_KEY_E            ;
	case 0x46            : return WLD_KEY_F            ;
	case 0x47            : return WLD_KEY_G            ;
	case 0x48            : return WLD_KEY_H            ;
	case 0x49            : return WLD_KEY_I            ;
	case 0x4A            : return WLD_KEY_J            ;
	case 0x4B            : return WLD_KEY_K            ;
	case 0x4C            : return WLD_KEY_L            ;
	case 0x4D            : return WLD_KEY_M            ;
	case 0x4E            : return WLD_KEY_N            ;
	case 0x4F            : return WLD_KEY_O            ;
	case 0x50            : return WLD_KEY_P            ;
	case 0x51            : return WLD_KEY_Q            ;
	case 0x52            : return WLD_KEY_R            ;
	case 0x53            : return WLD_KEY_S            ;
	case 0x54            : return WLD_KEY_T            ;
	case 0x55            : return WLD_KEY_U            ;
	case 0x56            : return WLD_KEY_V            ;
	case 0x57            : return WLD_KEY_W            ;
	case 0x58            : return WLD_KEY_X            ;
	case 0x59            : return WLD_KEY_Y            ;
	case 0x5A            : return WLD_KEY_Z            ;
	case VK_OEM_4        : return WLD_KEY_LEFT_BRACKET ;
	case VK_OEM_5        : return WLD_KEY_BACKSLASH    ;
	case VK_OEM_6        : return WLD_KEY_RIGHT_BRACKET;
	case VK_OEM_3        : return WLD_KEY_GRAVE_ACCENT ;
	case VK_OEM_102      : return WLD_KEY_WORLD_1      ;
	case VK_OEM_8        : return WLD_KEY_WORLD_2      ;
	case VK_NUMPAD0      : return WLD_KEY_KP_0         ;
	case VK_NUMPAD1      : return WLD_KEY_KP_1         ;
	case VK_NUMPAD2      : return WLD_KEY_KP_2         ;
	case VK_NUMPAD3      : return WLD_KEY_KP_3         ;
	case VK_NUMPAD4      : return WLD_KEY_KP_4         ;
	case VK_NUMPAD5      : return WLD_KEY_KP_5         ;
	case VK_NUMPAD6      : return WLD_KEY_KP_6         ;
	case VK_NUMPAD7      : return WLD_KEY_KP_7         ;
	case VK_NUMPAD8      : return WLD_KEY_KP_8         ;
	case VK_NUMPAD9      : return WLD_KEY_KP_9         ;
	case VK_DECIMAL      : return WLD_KEY_KP_DECIMAL   ;
	case VK_DIVIDE       : return WLD_KEY_KP_DIVIDE    ;
	case VK_MULTIPLY     : return WLD_KEY_KP_MULTIPLY  ;
	case VK_SUBTRACT     : return WLD_KEY_KP_SUBTRACT  ;
	case VK_ADD          : return WLD_KEY_KP_ADD       ;
	case VK_OEM_NEC_EQUAL: return WLD_KEY_KP_EQUAL     ;
	case VK_LSHIFT       : return WLD_KEY_LEFT_SHIFT   ;
	case VK_LCONTROL     : return WLD_KEY_LEFT_CONTROL ;
	case VK_LMENU        : return WLD_KEY_LEFT_ALT     ;
	case VK_LWIN         : return WLD_KEY_LEFT_SUPER   ;
	case VK_RSHIFT       : return WLD_KEY_RIGHT_SHIFT  ;
	case VK_RCONTROL     : return WLD_KEY_RIGHT_CONTROL;
	case VK_RMENU        : return WLD_KEY_RIGHT_ALT    ;
	case VK_RWIN         : return WLD_KEY_RIGHT_SUPER  ;
	case VK_APPS         : return WLD_KEY_MENU         ;
	case VK_F1           : return WLD_KEY_F1           ;
	case VK_F2           : return WLD_KEY_F2           ;
	case VK_F3           : return WLD_KEY_F3           ;
	case VK_F4           : return WLD_KEY_F4           ;
	case VK_F5           : return WLD_KEY_F5           ;
	case VK_F6           : return WLD_KEY_F6           ;
	case VK_F7           : return WLD_KEY_F7           ;
	case VK_F8           : return WLD_KEY_F8           ;
	case VK_F9           : return WLD_KEY_F9           ;
	case VK_F10          : return WLD_KEY_F10          ;
	case VK_F11          : return WLD_KEY_F11          ;
	case VK_F12          : return WLD_KEY_F12          ;
	case VK_F13          : return WLD_KEY_F13          ;
	case VK_F14          : return WLD_KEY_F14          ;
	case VK_F15          : return WLD_KEY_F15          ;
	case VK_F16          : return WLD_KEY_F16          ;
	case VK_F17          : return WLD_KEY_F17          ;
	case VK_F18          : return WLD_KEY_F18          ;
	case VK_F19          : return WLD_KEY_F19          ;
	case VK_F20          : return WLD_KEY_F20          ;
	case VK_F21          : return WLD_KEY_F21          ;
	case VK_F22          : return WLD_KEY_F22          ;
	case VK_F23          : return WLD_KEY_F23          ;
	case VK_F24          : return WLD_KEY_F24          ;
	default              : return NULL                 ;
	}
}
