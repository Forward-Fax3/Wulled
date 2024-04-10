#pragma once
#include "Engine/src/core/EngineCore.h"
#include "Engine/src/core/WLDMem.h"

#include "Engine/src/core/graphics/Renderer/VertexArray.h"


namespace WLD::Graphics::Renderer
{
	class WLD_API RendererAPI
	{
	public:
		enum class WLD_API API : uint8_t
		{
			None,
			OpenGL,
//			DirectX11,
			DirectX12,
			Vulkan,
		};

	public:
		virtual ~RendererAPI() = default;

		virtual void Init() = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		static inline API GetAPI() { return s_API; }
		static inline void SetAPI(API api) { s_API = api; }
		static inline API GetNextAPI() { return s_NextAPI; }
		static inline void SetNextAPI(API api) { s_NextAPI = api; }
		static inline void updateAPI() { s_API = s_NextAPI; }

	private:
		static API s_API;
		static API s_NextAPI;
	};
}