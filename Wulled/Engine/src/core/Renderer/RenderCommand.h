#pragma once
#include "Engine/src/core/EngineCore.h"
#include "Engine/src/core/Renderer/RendererAPI.h"


namespace WLD::Graphics::Renderer
{
	class WLD_API RenderCommand
	{
	public:
		inline static void Clear() { s_RendererAPI->Clear(); }

		inline static void DrawIndexed(const std::weak_ptr<VertexArray>& vertexArray) { s_RendererAPI->DrawIndexed(vertexArray); }

	private:
		static RendererAPI* s_RendererAPI;
	};
}