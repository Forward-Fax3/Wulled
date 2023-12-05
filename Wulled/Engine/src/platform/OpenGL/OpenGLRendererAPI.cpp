#include "wldpch.h"
#include "OpenGLRendererAPI.h"

#include "glatter/glatter.h"


namespace WLD::Graphics::OpenGL
{
	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::weak_ptr<Renderer::VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray.lock()->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}
