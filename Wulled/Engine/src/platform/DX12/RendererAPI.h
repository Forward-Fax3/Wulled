#pragma once
#include "Engine/src/core/EngineCore.h"
#include "Engine/src/core/graphics/Renderer/RendererAPI.h"


namespace WLD::Graphics::dx12
{
	class WLD_API DX12RendererAPI : public Renderer::RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<Renderer::VertexArray>& vertexArray) override;
	};
}