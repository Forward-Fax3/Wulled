#pragma once
#include "vulkan/vulkan.h"


namespace WLD
{
	class VulkanMemoryAllocator
	{
	public:
		VulkanMemoryAllocator() = delete;
		VulkanMemoryAllocator(VulkanMemoryAllocator&) = delete;
		VulkanMemoryAllocator(VulkanMemoryAllocator&&) = delete;
		VulkanMemoryAllocator& operator=(VulkanMemoryAllocator&) = delete;
		VulkanMemoryAllocator& operator=(VulkanMemoryAllocator&&) = delete;

		[[nodiscard]] VkDeviceMemory AllocateMemory(const VkBuffer buffer) const;
		void DeallocateMemory(VkDeviceMemory deviceMemory) const;

		static const VulkanMemoryAllocator& GetAllocator() { return *s_VkAllocator; }

	private: // functions
		// Only class that can make VulkanMemoryAllocator is the VulkanContext
		friend class VulkanContext;
		VulkanMemoryAllocator(const VkDevice device, const VkPhysicalDevice physicalDevice);
		~VulkanMemoryAllocator();

		inline uint32_t GetMemoryTypeIndex(const uint32_t typeFilter, const VkMemoryPropertyFlags properties) const;

	private: // variables
		VkDevice m_Device = nullptr;
		VkPhysicalDeviceMemoryProperties m_PhysicalDeviceMemoryProperties{};

		static VulkanMemoryAllocator* s_VkAllocator;
	};
}

#include "VkContext.h"
