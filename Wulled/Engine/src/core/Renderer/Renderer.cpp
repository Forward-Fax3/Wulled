#include "wldpch.h"
#include "Renderer.h"

namespace WLD
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(std::shared_ptr<PerspectiveCamera>& camera)
	{
		m_SceneData->camera = camera;
	}

	void Renderer::EndScene()
	{
		m_SceneData->camera.reset();
	}

	void Renderer::Submit(const std::weak_ptr<VertexArray>& vertexArray, std::shared_ptr<Shader>& shader)
	{
		shader->Bind();
		shader->SetUniformMat4fv("u_MVP", m_SceneData->camera->getProjection());
		vertexArray.lock()->Bind();
		vertexArray.lock()->GetIndexBuffer()->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}