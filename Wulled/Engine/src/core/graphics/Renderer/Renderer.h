#pragma once
#include "Engine/src/core/EngineCore.h"
#include "Engine/src/core/graphics/Renderer/RenderCommand.h"
#include "Engine/src/core/graphics/camera/PerspectiveCamera.h"
#include "Engine/src/core/graphics/Renderer/Shader.h"


namespace WLD::Graphics::Renderer
{
	class WLD_API Renderer
	{
	public:
		static void BeginScene(Ref<Camera::PerspectiveCamera>& camera);
		static void EndScene();

		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
		inline static void SetAPI(RendererAPI::API api) { RendererAPI::SetAPI(api); }
		inline static void SetNextAPI(RendererAPI::API api) { RendererAPI::SetNextAPI(api); }

	private:
		struct SceneData
		{
			Ref<Camera::PerspectiveCamera> camera;
		};

		static SceneData* m_SceneData;
	};
}