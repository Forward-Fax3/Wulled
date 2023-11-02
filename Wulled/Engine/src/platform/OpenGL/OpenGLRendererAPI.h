#pragma once
#include "Engine/src/core/EngineCore.h"
#include "Engine/src/core/Renderer/RendererAPI.h"

namespace WLD
{
	class WLD_API OpenGLRendererAPI : public RendererAPI
	{

		virtual void Clear() override;

		virtual void DrawIndexed(const std::weak_ptr<VertexArray>& vertexArray) override;
	};
}