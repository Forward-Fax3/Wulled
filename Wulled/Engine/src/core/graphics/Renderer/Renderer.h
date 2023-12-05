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
		static void BeginScene(std::shared_ptr<Camera::PerspectiveCamera>& camera);
		static void EndScene();

		static void Submit(const std::weak_ptr<VertexArray>& vertexArray, const std::weak_ptr<Shader>& shader);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
		inline static void SetAPI(RendererAPI::API api) { RendererAPI::SetAPI(api); }

	private:
		struct SceneData
		{
			std::shared_ptr<Camera::PerspectiveCamera> camera;
		};

		static SceneData* m_SceneData;
	};
}