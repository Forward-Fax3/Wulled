#pragma once
#include "Engine/src/core/EngineCore.h"
#include "Engine/src/core/graphics/Renderer/RenderCommand.h"
#include "Engine/src/core/graphics/camera/PerspectiveCamera.h"
#include "Engine/src/core/graphics/Renderer/Shader.h"
#include "UniformBuffer.h"


namespace WLD
{
	class WLD_API Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(Ref<Camera::PerspectiveCamera> camera);
		static void EndScene();

		static void SetShader(const Ref<Shader>& shader);

		static void DrawCube(const glm::vec3& position, const glm::vec3& size = glm::vec3(1.0f), const glm::vec4& colour = glm::vec4(1.0f));

		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));
		static void Submit(const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f), const glm::vec4& colour = glm::vec4(1.0f));
//		static void Submit(const glm::mat4& transform);

		static void SetBackgroundColour(const glm::vec4& colour) { s_SceneData->backgroundcolour = colour; }
//		static void SetBackgroundImage(const std::string& filepath);

		static const glm::vec4& GetBackgroundColour() { return s_SceneData->backgroundcolour; }

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
		inline static void SetAPI(RendererAPI::API api) { RendererAPI::SetAPI(api); }
		inline static RendererAPI::API GetNextAPI() { return RendererAPI::GetNextAPI(); }
		inline static void SetNextAPI(RendererAPI::API api) { RendererAPI::SetNextAPI(api); }

	private:
		struct SceneData
		{
			Ref<UniformBuffer> cameraUniformBuffer;
			Ref<Shader> shader;

			glm::vec4 backgroundcolour = glm::vec4(1.0f);
		};

		static SceneData* s_SceneData;
	};
}