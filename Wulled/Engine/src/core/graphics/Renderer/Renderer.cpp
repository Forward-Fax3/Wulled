#include "WLDPCH.h"
#include "WLDMem.h"
#include "Renderer.h"
#include "OpenGLShader.h"
#include "UniformBuffer.h"

#include "Buffer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace WLD
{
	Renderer::SceneData* Renderer::s_SceneData = nullptr;

	void Renderer::Init()
	{
		s_SceneData = CreateMemory(SceneData);
		s_SceneData->shader = nullptr;
		s_SceneData->cameraUBO = UniformBuffer::Create(sizeof(glm::mat4), 0);
		s_SceneData->dataUBO = UniformBuffer::Create(sizeof(DataUBO), 1);
		RenderCommand::CreateRendererAPI();
		RenderCommand::Init();
	}

	void Renderer::Shutdown()
	{
		RenderCommand::DeleteRendererAPI();
		DestroyMemory(s_SceneData);
	}

	void Renderer::BeginScene(Ref<Camera::PerspectiveCamera> camera)
	{
		s_SceneData->cameraUBO->SetData(glm::value_ptr(camera->GetProjection()), sizeof(glm::mat4));
	}

	void Renderer::EndScene()
	{
		s_SceneData->shader.reset();
	}

	void Renderer::SetShader(const Ref<Shader>& shader)
	{
		s_SceneData->shader = shader;
	}

	void Renderer::DrawCube(const glm::vec3& position, const glm::vec3& size, const glm::vec4& colour)
	{
		float vectors[] =
		{
			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f
		};

		uint32_t indices[] =
		{
			0, 1, 2, 2, 3, 0,
			1, 5, 6, 6, 2, 1,
			7, 6, 5, 5, 4, 7,
			4, 0, 3, 3, 7, 4,
			3, 2, 6, 6, 7, 3,
			4, 5, 1, 1, 0, 4
		};

		Ref<VertexBuffer> vBuffer(VertexBuffer::Create(vectors, sizeof(vectors)));
		Ref<IndexBuffer> iBuffer(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" }
		};
		vBuffer->SetLayout(layout);

		Ref<VertexArray> vertexArray = VertexArray::Create();

		vertexArray->AddVertexBuffer(vBuffer);
		vertexArray->SetIndexBuffer(iBuffer);

		glm::mat4 transform = glm::translate(glm::scale(glm::mat4(1.0f), size), position);

		Submit(vertexArray, transform, colour);
	}

	void Renderer::Submit(const WLD::Ref<VertexArray>& vertexArray, const WLD::Ref<Shader>& shader, const glm::mat4& transform)
	{
//		shader->Bind();
//		shader->SetMat4("u_MVP", s_SceneData->camera->getProjection());
//		shader->SetMat4("u_Transform", transform);
//		vertexArray->Bind();
//		vertexArray->GetIndexBuffer()->Bind();
//		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::Submit(const WLD::Ref<VertexArray>& vertexArray, const glm::mat4& transform, const glm::vec4& colour)
	{
		vertexArray->Bind();
		vertexArray->GetIndexBuffer()->Bind();
		s_SceneData->shader->Bind();

		DataUBO data;
		data.transform = transform;
		data.colour = colour;
		s_SceneData->dataUBO->SetData(&data);
//		s_SceneData->dataUBO->SetData(&transform, sizeof(transform), 0);
//		s_SceneData->dataUBO->SetData(&colour, sizeof(colour), sizeof(transform));
		RenderCommand::DrawIndexed(vertexArray);
	}
}