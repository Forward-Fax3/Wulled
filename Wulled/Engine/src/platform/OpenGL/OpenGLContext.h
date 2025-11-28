#pragma once
#include "Engine/src/core/EngineCore.h"

#include "Engine/src/core/graphics/GraphicsContext.h"

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
		virtual void MakeCurrent() const override;
		virtual void SetVsync(const bool vsync) override;
		virtual void ImGuiInit() const override;
		virtual void ImGuiBegin() const override;
		virtual void ImGuiEnd() const override;
		virtual void ImGuiShutdown() const override;
		virtual void Info() override;

	private:
		SDL_GLContext m_Context;
		
		static inline HGLRC s_hglrc;
	};
}
