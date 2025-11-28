#include "wldpch.h"
#include "OpenGLRendererAPI.h"
#include "Renderer.h"

#include "SDL.h"
#include "GL/glew.h"
// #include "glad/glad.h"


namespace WLD
{
	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glDepthMask(GL_TRUE);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glFrontFace(GL_CCW);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		const glm::vec4& colour = Renderer::GetBackgroundColour();
		glClearColor(colour.r, colour.g, colour.b, colour.a);
	}

	void OpenGLRendererAPI::DrawIndexed(const WLD::Ref<VertexArray> vertexArray)
	{
		if (m_WireFrame)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		uint32_t count = vertexArray->GetIndexBuffer()->GetCount();

		vertexArray->GetIndexBuffer()->Bind();
		vertexArray->Bind();
		for (Ref<VertexBuffer> vertexBuffer : vertexArray->GetVertexBuffers())
		{
			vertexBuffer->Bind();
			glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		}
	}
}
