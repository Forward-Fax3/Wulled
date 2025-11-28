#include "wldpch.h"
#include "EngineCore.h"

#include "VkUniformBuffer.h"


namespace WLD
{
	VkUniformBuffer::VkUniformBuffer(uint32_t size, uint32_t binding)
	{
		LOG_CORE_CRITICAL("-----> NEED TO IMPLEMENT VK UBO <-----");
	}

	VkUniformBuffer::~VkUniformBuffer()
	{
	}

	void VkUniformBuffer::SetData(const void* data, uint32_t size, uint32_t offset)
	{
	}
}