#pragma once
#include "Engine/src/core/EngineCore.h"
#include "Engine/src/core/graphics/Renderer/RendererAPI.h"


namespace WLD::Graphics::Renderer
{
	class WLD_API RenderCommand
	{
	public:
		static void CreateRendererAPI();
		inline static void DeleteRendererAPI() { delete s_RendererAPI; }

		inline static void Clear() { s_RendererAPI->Clear(); }

		inline static void DrawIndexed(const std::weak_ptr<VertexArray>& vertexArray) { s_RendererAPI->DrawIndexed(vertexArray); }

	private:
		inline static RendererAPI* s_RendererAPI;
	};
}