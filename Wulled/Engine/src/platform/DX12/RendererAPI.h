#pragma once
#include "Engine/src/core/EngineCore.h"
#include "Engine/src/core/graphics/Renderer/RendererAPI.h"


namespace WLD::Graphics::dx12
{
	class WLD_API DX12RendererAPI : public Renderer::RendererAPI
	{
		virtual void Clear() override;

		virtual void DrawIndexed(const std::weak_ptr<Renderer::VertexArray>& vertexArray) override;
	};
}