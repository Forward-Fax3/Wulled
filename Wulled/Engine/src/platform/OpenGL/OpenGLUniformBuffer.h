#pragma once
#include "Engine/src/Core/Graphics/Renderer/UniformBuffer.h"


namespace WLD
{
	class OpenGLUniformBuffer : public UniformBuffer
	{
	public:
		OpenGLUniformBuffer(uint32_t size, uint32_t binding);
		virtual ~OpenGLUniformBuffer();

		virtual void SetData(const void* data, uint32_t size = 0, uint32_t offset = 0) override;

	private:
		uint32_t m_RendererID;
		size_t m_Size;
	};
}
