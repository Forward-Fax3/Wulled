#include "wldpch.h"
#include "WLDMem.h"
#include "OpenGL/ImGui/VP.h"
#include "glatter/glatter.h"
#include "GraphicsContext.h"
#include "window.h"
#include <wingdi.h>


void WLD::ImGuiVP::CreateVPWindow(ImGuiViewport* viewport)
{
	WLD_CORE_ASSERT((viewport->RendererUserData == NULL), "Already created viewport");

	Graphics::GraphicsContext* context = Graphics::GraphicsContext::createGraphicsContext((HWND*)&viewport->PlatformHandle, WindowProps(L"Wulled", 1280U, 720U));
	context->CreateDevice();
	viewport->RendererUserData = context;
}

void WLD::ImGuiVP::DestroyVPWindow(ImGuiViewport* viewport)
{
	if (viewport->RendererUserData)
	{
		Graphics::GraphicsContext* context = (Graphics::GraphicsContext*)viewport->RendererUserData;
		DestroyMemory(context);
		viewport->RendererUserData = NULL;
	}
}

void WLD::ImGuiVP::RenderVPWindow(ImGuiViewport* viewport, void* render_arg)
{
	// Activate the platform window DC in the OpenGL rendering context
	Graphics::GraphicsContext* context = (Graphics::GraphicsContext*)viewport->RendererUserData;

	if (context)
		context->MakeCurrent();
}

void WLD::ImGuiVP::SwapVPBuffers(ImGuiViewport* viewport, void* render_arg)
{
	Graphics::GraphicsContext* context = (Graphics::GraphicsContext*)viewport->RendererUserData;

	if (context)
		context->SwapBuffers();
}