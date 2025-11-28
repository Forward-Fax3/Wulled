#pragma once
#include "Engine/src/core/EngineCore.h"
#include "SDL.h"


namespace WLD
{
	struct WLD_API WindowProps;
}

namespace WLD
{
	class WLD_API GraphicsContext
	{
	public:
		inline GraphicsContext(WindowProps& Data)
			: m_WindowProps(Data) {}
		virtual ~GraphicsContext() = default;

		virtual void CreateDevice() = 0;
		virtual void Shutdown() = 0;
		virtual void SwapBuffers() = 0;
		virtual void OnWindowResize() = 0;
		virtual void MakeCurrent() const = 0;
		virtual void SetVsync(const bool vsync) = 0;
		virtual void ImGuiInit() const = 0;
		virtual void ImGuiBegin() const = 0;
		virtual void ImGuiEnd() const = 0;
		virtual void ImGuiShutdown() const = 0;
		virtual void Info() = 0;

		static GraphicsContext* createGraphicsContext(WindowProps& Data);

	protected:
		WindowProps& m_WindowProps;
	};
}
