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

		virtual void CreateDevice() = 0;
		virtual void Shutdown() = 0;
		virtual void SwapBuffers() = 0;
		virtual void OnWindowResize() = 0;
		virtual void MakeCurrent() = 0;
		virtual void SetVsync(const bool vsync) = 0;
		virtual void ImGuiInit() = 0;
		virtual void ImGuiBegin() = 0;
		virtual void ImGuiEnd() = 0;
		virtual void ImGuiShutdown() = 0;
		virtual void Info() = 0;

		static GraphicsContext* createGraphicsContext(WindowProps& Data);

	protected:
		WindowProps& m_WindowProps;
	};
}
