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
			DX12 = DirectX12,
			D3D12 = DirectX12,
		};

	public:
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::weak_ptr<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_API; }
		inline static void SetAPI(API api) { s_NextAPI = api; }
		inline static void updateAPI() { s_API = s_NextAPI; }

	private:
		static API s_API;
		static API s_NextAPI;
	};
}