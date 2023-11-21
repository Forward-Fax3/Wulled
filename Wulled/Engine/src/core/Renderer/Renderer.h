#pragma once
#include "Engine/src/core/EngineCore.h"
#include "Engine/src/core/Renderer/RenderCommand.h"
#include "Engine/src/core/Renderer/PerspectiveCamera.h"
#include "Engine/src/core/Renderer/Shader.h"


namespace WLD::Graphics::Renderer
{
	class WLD_API Renderer
	{
	public:
		static void BeginScene(std::shared_ptr<Camera::PerspectiveCamera>& camera);
		static void EndScene();

		static void Submit(const std::weak_ptr<VertexArray>& vertexArray, const std::weak_ptr<Shader>& shader);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			std::shared_ptr<Camera::PerspectiveCamera> camera;
		};

		static SceneData* m_SceneData;
	};
}