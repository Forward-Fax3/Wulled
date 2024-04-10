#pragma once
#include "Engine/src/core/WLDMem.h"
#include "Engine/src/core/EngineCore.h"
#include "Engine/src/core/graphics/Renderer/RendererAPI.h"


namespace WLD::Graphics::Renderer
{
	class WLD_API RenderCommand
	{
	public:
		static void CreateRendererAPI();
		static void DeleteRendererAPI();

		inline static void Init() { s_RendererAPI->Init(); }

		inline static void Clear() { s_RendererAPI->Clear(); }

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) { s_RendererAPI->DrawIndexed(vertexArray); }

	private:
		static RendererAPI* s_RendererAPI;
	};
}