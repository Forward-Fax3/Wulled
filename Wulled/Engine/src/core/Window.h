#pragma once
#include "Engine/src/Core/EngineCore.h"
#include "Engine/src/core/WLDMem.h"
#include "Engine/src/Core/Events/Event.h"
#include "Engine/src/core/Events/windowEvent.h"
#include "Engine/src/core/graphics/GraphicsContext.h"
#include "Engine/src/core/WLDMem.h"

#include <SDL.h>

namespace WLD
{
#if defined(_DEBUG)
	void WLD_SDLCheckError(int32_t sdlResult);
	void WLD_SDLCheckError(SDL_bool sdlResult);
	void WLD_SDLCheckError(SDL_Window* sdlResult);
	void WLD_SDLCheckError(SDL_GLContext sdlResult);
#else
	#define WLD_SDLCheckError(x) x
#endif

	struct WLD_API WindowProps
	{
		wchar_t* Title = nullptr;
		char* TitleC = nullptr;
		uint32_t Width = NULL, Height = NULL;
		SDL_Window* SDLWindow = nullptr;
		SDL_WindowFlags Flags = (SDL_WindowFlags)0;

		WindowProps();
		WindowProps(const char* title, uint32_t width = 1280, uint32_t height = 720);
		WindowProps(const wchar_t* title, uint32_t width = 1280, uint32_t height = 720);
		WindowProps(WindowProps&& props) noexcept;
		~WindowProps();

		WindowProps& operator=(WindowProps&& props) noexcept;

		// Copying is not allowed
		// this is due to WindowProps dealling with it own memory creation and deletion
		// and copying would cause memory access violations once the memory is deleted
		// only operations move is allowed and using pointers/referances to the object
		// is allowed
 		WindowProps(const WindowProps&) = delete;
		WindowProps& operator=(const WindowProps&) = delete;
		
	private:
		uint8_t m_CreatedMethod; // bit 0 = True -> default, bit 1 = True -> wide char, bit 1 = False -> char
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

		virtual SDL_Window* GetNativeWindow() const = 0;
		virtual GraphicsContext& GetGraphicsContext() const = 0;

		virtual void onWindowResize(uint32_t width, uint32_t height) = 0;

		static Window* Create(WindowProps& props);
 	};
}
