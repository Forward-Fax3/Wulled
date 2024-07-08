#pragma once
#include "Engine/src/core/graphics/Renderer/UniformBuffer.h"


namespace WLD
{
	class VkUniformBuffer : public UniformBuffer
	{
		public:
		VkUniformBuffer(uint32_t size, uint32_t binding);
		virtual ~VkUniformBuffer();

		virtual void SetData(const void* data, uint32_t size = 0, uint32_t offset = 0) override;
	};
}
