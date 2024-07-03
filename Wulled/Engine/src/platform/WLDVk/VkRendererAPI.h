#pragma once
#include "RendererAPI.h"


namespace WLD
{
	class WLD_API VkRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void Clear() override;

		virtual void DrawIndexed(const WLD::Ref<VertexArray>& vertexArray) override;
	};
}
