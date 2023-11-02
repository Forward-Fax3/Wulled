#pragma once
#include "Engine/src/core/EngineCore.h"

#include "Engine/src/core/Renderer/VertexArray.h"


namespace WLD
{
	class WLD_API RendererAPI
	{
	public:
		enum class WLD_API API
		{
			None,
			OpenGL,
//			DirectX11,
//			DirectX12,
		};

	public:
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::weak_ptr<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};
}