#pragma once
#include "Engine/src/core/EngineCore.h"
#include "Engine/src/core/graphics/Renderer/RendererAPI.h"

namespace WLD
{
	class WLD_API OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void Clear() override;

		virtual void BeginScene() override {};
		virtual void EndScene() override {};

		virtual void DrawIndexed(const WLD::Ref<VertexArray> vertexArray) override;
	};
}