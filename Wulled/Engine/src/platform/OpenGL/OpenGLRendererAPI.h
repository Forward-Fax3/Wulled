#pragma once
#include "Engine/src/core/EngineCore.h"
#include "Engine/src/core/Renderer/RendererAPI.h"

namespace WLD::Graphics::OpenGL
{
	class WLD_API OpenGLRendererAPI : public Renderer::RendererAPI
	{

		virtual void Clear() override;

		virtual void DrawIndexed(const std::weak_ptr<Renderer::VertexArray>& vertexArray) override;
	};
}