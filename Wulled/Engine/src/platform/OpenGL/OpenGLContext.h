#pragma once
#include "Engine/src/Core/EngineCore.h"

#include "Engine/src/Core/Graphics/GraphicsContext.h"

#include "GL/glew.h"
#include "SDL.h"


namespace WLD
{
	class WLD_API OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(WindowProps& props);

		virtual void CreateDevice() override;
		virtual void Shutdown() override;
		virtual void SwapBuffers() override;
		virtual void OnWindowResize() override;
		virtual void MakeCurrent() override;
		virtual void SetVsync(const bool vsync) override;
		virtual void ImGuiInit() override;
		virtual void ImGuiBegin() override;
		virtual void ImGuiEnd() override;
		virtual void ImGuiShutdown() override;
		virtual void Info() override;

	private:
		SDL_GLContext m_Context;
		
		static inline HGLRC s_hglrc;
	};
}
