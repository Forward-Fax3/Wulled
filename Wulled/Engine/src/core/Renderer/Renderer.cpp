#include "wldpch.h"
#include "Renderer.h"

namespace WLD::Graphics::Renderer
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(std::shared_ptr<Camera::PerspectiveCamera>& camera)
	{
		m_SceneData->camera = camera;
	}

	void Renderer::EndScene()
	{
		m_SceneData->camera.reset();
	}

	void Renderer::Submit(const std::weak_ptr<VertexArray>& vertexArray, const std::weak_ptr<Shader>& shader)
	{
		shader.lock()->Bind();
		shader.lock()->SetUniformMat4fv("u_MVP", m_SceneData->camera->getProjection());
		vertexArray.lock()->Bind();
		vertexArray.lock()->GetIndexBuffer()->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}