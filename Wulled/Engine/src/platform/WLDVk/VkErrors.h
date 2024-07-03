#pragma once
#include "Engine/src/core/EngineCore.h"
#include <vulkan/vulkan.h>


namespace WLD
{
#ifdef _DEBUG
	inline static void WLD_VkCheckError(VkResult vkResult)
	{
		WLD_CORE_ASSERT(vkResult == VK_SUCCESS, "Vulkan Error: {0}", (int32_t)vkResult);
	}

	inline static void WLD_VkCheckError(VkQueue vkResult)
	{
		WLD_CORE_ASSERT(vkResult, "Vulkan Queue Error: {0}");
	}
#else
#define WLD_VkCheckError(x) x
#endif
}