#pragma once
#include "Engine/src/core/EngineCore.h"
#include "Engine/src/core/Renderer/RenderCommand.h"


namespace WLD
{
	class WLD_API Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::weak_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}