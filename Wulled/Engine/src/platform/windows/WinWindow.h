#pragma once
#include "Engine/src/core/Window.h"
#include "Engine/src/core/graphics/GraphicsContext.h"

#include "GL/glew.h"
#include "SDL.h"


namespace WLD
{
	class Application;

	struct EventData
	{
		SDL_Event* event;
		bool isFinished = false;

		inline EventData(SDL_Event* e)
			: event(e)
		{
		}

		inline ~EventData()
		{
			DestroyMemory(event);
		}

		void callEvent() const;
	};

	class WinWindow : public Window
	{
	public:
		WinWindow(WindowProps& props);
		virtual ~WinWindow() override;
		
		void OnUpdate() override;

		inline uint32_t GetWidth() const override { return m_Data.props.Width; }
		inline uint32_t GetHeight() const override { return m_Data.props.Height; }

		// Window attributes
		inline virtual void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		inline virtual EventCallbackFn GetEventCallback() const override { return m_Data.EventCallback; }

		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		char* GetTitle() const { return m_Data.props.TitleC; }
		wchar_t* GetTitleW() const { return m_Data.props.Title; }

		virtual inline const SDL_Window* GetNativeWindow() const override { return m_SDLWindow; }
		virtual inline const GraphicsContext& GetGraphicsContext() const override { return *m_Context; }

		virtual void OnWindowResize(uint32_t width, uint32_t height) override;

	private:
		void Init();
		void Shutdown();

		void ClearEventQueue();
		void CheckEvents();

		void WindowResize() const;

	private:
		SDL_Window* m_SDLWindow;
		std::vector<EventData*> m_IssuedEvents;

		GraphicsContext* m_Context;

		struct WindowData
		{
			inline WindowData(WindowProps& props)
				: props(props) {}

			WindowProps& props;
			bool VSync = false;
			EventCallbackFn EventCallback;
		} m_Data;

		WinWindowEvent* m_CallEventSet = nullptr;

		bool m_SDLWindowNeedsResize = false;

		friend struct EventData;
	};
}