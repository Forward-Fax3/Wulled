#pragma once
#include "Engine/src/Core/WLDMem.h"
#include "Engine/src/Core/EngineCore.h"
#include "Engine/src/Core/Graphics/Renderer/RendererAPI.h"


namespace WLD
{
	class WLD_API RenderCommand
	{
	public:
		static void CreateRendererAPI();
		static void DeleteRendererAPI();

		inline static void Init() { s_RendererAPI->Init(); }

		inline static void Clear() { s_RendererAPI->Clear(); }

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) { s_RendererAPI->DrawIndexed(vertexArray); }

		inline static void ToggleWireFrame() { s_RendererAPI->ToggleWireFrame(); }

	private:
		static RendererAPI* s_RendererAPI;
	};
}