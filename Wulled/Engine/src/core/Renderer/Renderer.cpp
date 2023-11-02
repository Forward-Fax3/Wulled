#include "wldpch.h"
#include "Renderer.h"

namespace WLD
{
	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::weak_ptr<VertexArray>& vertexArray)
	{
		vertexArray.lock()->Bind();
		vertexArray.lock()->GetIndexBuffer()->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}