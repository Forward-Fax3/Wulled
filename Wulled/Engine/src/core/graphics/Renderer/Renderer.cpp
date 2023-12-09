#include "wldpch.h"
#include "Renderer.h"
#include "OpenGL/Shader.h"


namespace WLD::Graphics::Renderer
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(Ref<Camera::PerspectiveCamera>& camera)
	{
		m_SceneData->camera = camera;
	}

	void Renderer::EndScene()
	{
		m_SceneData->camera.reset();
	}

	void Renderer::Submit(const WLD::Ref<VertexArray>& vertexArray, const WLD::Ref<Shader>& shader, const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGL::OpenGLShader>(shader)->SetUniformMat4fv("u_MVP", m_SceneData->camera->getProjection());
		std::dynamic_pointer_cast<OpenGL::OpenGLShader>(shader)->SetUniformMat4fv("u_Transform", transform);
		if (GetAPI() == RendererAPI::API::OpenGL)
		{
			vertexArray->Bind();
			vertexArray->GetIndexBuffer()->Bind();
		}
		RenderCommand::DrawIndexed(vertexArray);
	}
}