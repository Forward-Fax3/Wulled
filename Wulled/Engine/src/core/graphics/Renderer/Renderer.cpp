#include "wldpch.h"
#include "WLDMem.h"
#include "Renderer.h"
#include "OpenGL/Shader.h"


namespace WLD::Graphics::Renderer
{
	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		RenderCommand::CreateRendererAPI();
		RenderCommand::Init();
	}

	void Renderer::Shutdown()
	{
		RenderCommand::DeleteRendererAPI();
	}

	void Renderer::BeginScene(Ref<Camera::PerspectiveCamera> camera)
	{
		s_SceneData->camera = camera;
	}

	void Renderer::EndScene()
	{
		s_SceneData->camera.reset();
	}

	void Renderer::Submit(const WLD::Ref<VertexArray>& vertexArray, const WLD::Ref<Shader>& shader, const glm::mat4& transform)
	{
		shader->Bind();
		((Graphics::OpenGL::OpenGLShader*)shader.get())->SetUniformMat4fv("u_MVP", s_SceneData->camera->getProjection());
		((Graphics::OpenGL::OpenGLShader*)shader.get())->SetUniformMat4fv("u_Transform", transform);
		if (GetAPI() == RendererAPI::API::OpenGL)
		{
			vertexArray->Bind();
			vertexArray->GetIndexBuffer()->Bind();
		}
		RenderCommand::DrawIndexed(vertexArray);
	}
}