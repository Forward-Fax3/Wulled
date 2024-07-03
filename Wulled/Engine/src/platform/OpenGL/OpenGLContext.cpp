#include "wldpch.h"
#undef EN_ENABLE_ASSERTS
#define EN_ENABLE_ASSERTS

#include "Application.h"
#include "OpenGLContext.h"
#include "Renderer.h"

#include "SDL.h"
#include "GL/glew.h"

#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_SDL2.h"


namespace WLD
{
	OpenGLContext::OpenGLContext(WindowProps& props)
		: GraphicsContext(props), m_Context(nullptr)
	{
		m_WindowProps.Flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	}

	void OpenGLContext::CreateDevice()
	{
		// Use OpenGL 4.6 core profile
		WLD_SDLCheckError(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4));
		WLD_SDLCheckError(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6));
		WLD_SDLCheckError(SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE));

		// Turn on double buffering with a 24bit Z buffer
//		WLD_SDLCheckError(SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1));
//		WLD_SDLCheckError(SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24));

		m_Context = SDL_GL_CreateContext(m_WindowProps.SDLWindow);
		WLD_SDLCheckError(m_Context);
		
		GLenum err = glewInit();
		WLD_CORE_ASSERT(err == GLEW_OK, "Failed to initialize GLEW! Error: {0}", (char*)glewGetErrorString(err));

		auto version = glGetString(GL_VERSION);
		LOG_CORE_INFO("OpenGL Version: {0}", (char*)version);

		auto isOpenGL46 = GLEW_VERSION_4_5;
		if (isOpenGL46)
			LOG_CORE_INFO("OpenGL 4.6 is supported!");
		else
			LOG_CORE_FATAL("OpenGL 4.6 is not supported!");
		
		return; // TODO: add NON fail state close
	}

	void OpenGLContext::Shutdown()
	{
		SDL_GL_DeleteContext(m_Context);
	}

	void OpenGLContext::SwapBuffers()
	{
		SDL_GL_SwapWindow(m_WindowProps.SDLWindow);
	}

	void OpenGLContext::OnWindowResize()
	{
		glViewport(0, 0, m_WindowProps.Width, m_WindowProps.Height);
	}

	void OpenGLContext::MakeCurrent()
	{
		WLD_SDLCheckError(SDL_GL_MakeCurrent(m_WindowProps.SDLWindow, m_Context));
	}

	void OpenGLContext::SetVsync(const bool vsync)
	{
		WLD_SDLCheckError(SDL_GL_SetSwapInterval(vsync));
	}

	void OpenGLContext::ImGuiInit()
	{
		// Setup Platform/Renderer bindings
		ImGui_ImplSDL2_InitForOpenGL(m_WindowProps.SDLWindow, m_Context);
		ImGui_ImplOpenGL3_Init();
	}

	void OpenGLContext::ImGuiBegin()
	{
		ImGui_ImplOpenGL3_NewFrame();
	}

	void OpenGLContext::ImGuiEnd()
	{
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void OpenGLContext::ImGuiShutdown()
	{
		ImGui_ImplOpenGL3_Shutdown();
	}

	void OpenGLContext::Info()
	{
		LOG_CORE_INFO
		(
			"OpenGL Info:\n"
			"\t\t\t  OpenGL Version: {0}\n"
			"\t\t\t  OpenGL Renderer: {1}\n"
			"\t\t\t  OpenGL Version: {2}",
			(const char*)glGetString(GL_VENDOR),   // 0
			(const char*)glGetString(GL_RENDERER), // 1
			(const char*)glGetString(GL_VERSION)   // 2
		);
	}
}
