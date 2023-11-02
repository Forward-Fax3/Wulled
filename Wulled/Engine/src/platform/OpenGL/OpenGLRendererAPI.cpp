#include "wldpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>


namespace WLD
{
	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::weak_ptr<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray.lock()->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}
