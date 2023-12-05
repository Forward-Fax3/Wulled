#pragma once
#include "Engine/src/core/Window.h"
#include "Engine/src/core/graphics/GraphicsContext.h"

#include "glatter/glatter.h"


namespace WLD
{
	class WinWindow : public Window
	{
	public:
		WinWindow(const WindowProps& props);
		virtual ~WinWindow();
		
		void OnUpdate() override;

		inline uint32_t GetWidth() const override { return m_Data.Width; }
		inline uint32_t GetHeight() const override { return m_Data.Height; }

		// Window attributes
		inline virtual void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		inline virtual EventCallbackFn GetEventCallback() const override { return m_Data.EventCallback; }

		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual HWND& GetNativeWindow()                                            const override { return (HWND&)m_HWND; }
		inline virtual HWND* GetNativeWindowPtr()                                         const override { return (HWND*)&m_HWND; }
		inline virtual WNDCLASS& GetNativeWindowClass()                                   const override { return (WNDCLASS&)m_WindowClass; }
		inline virtual WNDCLASS* GetNativeWindowClassPtr()                                const override { return (WNDCLASS*)&m_WindowClass; }
		inline virtual WinEventCallBack& GetNativeEventCallback()                         const override { return (WinEventCallBack&)*m_WindowEvent; }
		inline virtual WinEventCallBack* GetNativeEventCallbackPtr()                      const override { return (WinEventCallBack*)m_WindowEvent; }
		inline virtual Graphics::Renderer::GraphicsContext& GetNativeGraphicsContext()    const override { return (Graphics::Renderer::GraphicsContext&)*m_Context; }
		inline virtual Graphics::Renderer::GraphicsContext* GetNativeGraphicsContextPtr() const override { return (Graphics::Renderer::GraphicsContext*)m_Context; }
		
		virtual void onWindowResize(uint32_t width, uint32_t height) override { m_Context->OnWindowResize(width, height); }

		struct WindowData
		{
			wchar_t* Title = nullptr;
			char* TitleC = nullptr;
			uint32_t Width = NULL, Height = NULL;
			bool VSync = false;

			EventCallbackFn EventCallback;
		};	

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		WNDCLASSEXW m_WindowClass;
		HWND m_HWND;

		Graphics::Renderer::GraphicsContext* m_Context;


		WindowData m_Data;

		WinEventCallBack* m_WindowEvent = nullptr;
		static inline WinEventCallBack** s_WindowEvent = nullptr;
		static LRESULT CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
}