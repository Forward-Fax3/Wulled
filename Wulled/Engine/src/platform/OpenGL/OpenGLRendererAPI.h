#pragma once
#include "Engine/src/Core/EngineCore.h"
#include "Engine/src/Core/Graphics/Renderer/RendererAPI.h"

namespace WLD
{
	class WLD_API OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void Clear() override;

		virtual void DrawIndexed(const WLD::Ref<VertexArray>& vertexArray) override;
	};
}