#include "WLDPCH.h"
#include "WLDMem.h"
#include "OpenGLImGui/VP.h"
#include "GL/glew.h"
// #include "glad/glad.h"
#include "GraphicsContext.h"
#include "Window.h"
#include <wingdi.h>


void WLD::ImGuiVP::CreateVPWindow(ImGuiViewport* viewport)
{
	WLD_CORE_ASSERT((viewport->RendererUserData == NULL), "Already created viewport");

//	Graphics::GraphicsContext* context = Graphics::GraphicsContext::createGraphicsContext((HWND*)&viewport->PlatformHandle, WindowProps(L"Wulled", 1280U, 720U));
//	context->CreateDevice();
//	viewport->RendererUserData = context;
}

void WLD::ImGuiVP::DestroyVPWindow(ImGuiViewport* viewport)
{
	if (viewport->RendererUserData)
	{
		GraphicsContext* context = (GraphicsContext*)viewport->RendererUserData;
		DestroyMemory(context);
		viewport->RendererUserData = NULL;
	}
}

void WLD::ImGuiVP::RenderVPWindow(ImGuiViewport* viewport, void* render_arg)
{
	// Activate the platform window DC in the OpenGL rendering context
	GraphicsContext* context = (GraphicsContext*)viewport->RendererUserData;

	if (context)
		context->MakeCurrent();
}

void WLD::ImGuiVP::SwapVPBuffers(ImGuiViewport* viewport, void* render_arg)
{
	GraphicsContext* context = (GraphicsContext*)viewport->RendererUserData;

	if (context)
		context->SwapBuffers();
}