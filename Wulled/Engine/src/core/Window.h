#pragma once
#include <windows.h>

#include "Engine/src/Core/EngineCore.h"
#include "Engine/src/Core/Events/Event.h"
#include "Engine/src/core/Events/windowEvent.h"
#include "Engine/src/core/graphics/GraphicsContext.h"

#include "glatter/glatter.h"


namespace WLD
{
	struct WLD_API WindowProps
	{
		wchar_t* Title;
		uint32_t Width, Height;

		WindowProps(const wchar_t* title = L"Basic Engine", uint32_t width = 1280, uint32_t height = 720)
			: Title((wchar_t*)title), Width(width), Height(height) {}
	};

	// Interface representing a desktop system window
	class WLD_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn&) = 0;
		virtual EventCallbackFn GetEventCallback() const = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual HWND& GetNativeWindow() const = 0;
		virtual HWND* GetNativeWindowPtr() const = 0;
		virtual WNDCLASS& GetNativeWindowClass() const = 0;
		virtual WNDCLASS* GetNativeWindowClassPtr() const = 0;
		virtual WinEventCallBack& GetNativeEventCallback() const = 0;
		virtual WinEventCallBack* GetNativeEventCallbackPtr() const = 0;
		virtual Graphics::GraphicsContext& GetNativeGraphicsContext() const = 0;
		virtual Graphics::GraphicsContext* GetNativeGraphicsContextPtr() const = 0;

		virtual void onWindowResize(uint32_t width, uint32_t height) = 0;

		static Window* Create(const WindowProps& props = WindowProps());
 	};
}
