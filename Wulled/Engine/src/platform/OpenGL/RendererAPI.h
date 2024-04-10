#pragma once
#include "Engine/src/core/EngineCore.h"
#include "Engine/src/core/graphics/Renderer/RendererAPI.h"

namespace WLD::Graphics::OpenGL
{
	class WLD_API OpenGLRendererAPI : public Renderer::RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void Clear() override;

		virtual void DrawIndexed(const WLD::Ref<Renderer::VertexArray>& vertexArray) override;
	};
}