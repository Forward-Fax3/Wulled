#pragma once
#include "Engine/src/core/EngineCore.h"

#include "Engine/src/core/graphics/Renderer/VertexArray.h"


namespace WLD::Graphics::Renderer
{
	class WLD_API RendererAPI
	{
	public:
		enum class WLD_API API
		{
			None,
			OpenGL,
//			DirectX11,
			DirectX12,
		};

	public:
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::weak_ptr<VertexArray>& vertexArray) = 0;

		static inline API GetAPI() { return s_API; }
		static inline void SetNextAPI(API api) { s_NextAPI = api; }
		static inline void SetAPI(API api) { s_API = api; }
		static inline void updateAPI() { s_API = s_NextAPI; }

	private:
		static API s_API;
		static API s_NextAPI;
	};
}