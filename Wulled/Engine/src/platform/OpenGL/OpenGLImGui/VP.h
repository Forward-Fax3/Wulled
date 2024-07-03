#pragma once
#include "EngineCore.h"
#include "imgui.h"


namespace WLD
{
	class WLD_API ImGuiVP
	{
	public:
		static void CreateVPWindow(ImGuiViewport* veiwport);
		static void DestroyVPWindow(ImGuiViewport* veiwport);
		static void RenderVPWindow(ImGuiViewport* veiwport, void* render_arg);
		static void SwapVPBuffers(ImGuiViewport* veiwport, void* render_arg);
	};
}
