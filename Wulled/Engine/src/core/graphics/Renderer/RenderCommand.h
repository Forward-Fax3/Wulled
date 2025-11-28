#pragma once
#include "Engine/src/core/WLDMem.h"
#include "Engine/src/core/EngineCore.h"
#include "Engine/src/core/graphics/Renderer/RendererAPI.h"


namespace WLD
{
	class WLD_API RenderCommand
	{
	public:
		static void CreateRendererAPI();
		static void DeleteRendererAPI();

		inline static void Init() { s_RendererAPI->Init(); }

		inline static void Clear() { s_RendererAPI->Clear(); }

		inline static void BeginScene() { s_RendererAPI->BeginScene(); }
		inline static void EndScene() { s_RendererAPI->EndScene(); }

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) { s_RendererAPI->DrawIndexed(vertexArray); }

		inline static void ToggleWireFrame() { s_RendererAPI->ToggleWireFrame(); }

	private:
		static RendererAPI* s_RendererAPI;
	};
}