#include "VkErrors.h"

#include "VkMemoryAllocator.h"


namespace WLD
{
	VulkanMemoryAllocator* VulkanMemoryAllocator::s_VkAllocator = nullptr;

	VulkanMemoryAllocator::VulkanMemoryAllocator(const VkDevice device, const VkPhysicalDevice physicalDevice)
		: m_Device(device)
	{
		s_VkAllocator = this;

		vkGetPhysicalDeviceMemoryProperties(physicalDevice, &m_PhysicalDeviceMemoryProperties);
	}

	VulkanMemoryAllocator::~VulkanMemoryAllocator()
	{
		s_VkAllocator = nullptr;
		m_Device = nullptr;
	}

	VkDeviceMemory VulkanMemoryAllocator::AllocateMemory(const VkBuffer buffer) const
	{
		VkMemoryRequirements memoryRequirements{};
		vkGetBufferMemoryRequirements(m_Device, buffer, &memoryRequirements);

		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memoryRequirements.size;
		allocInfo.memoryTypeIndex = this->GetMemoryTypeIndex(memoryRequirements.memoryTypeBits, static_cast<const VkMemoryPropertyFlags>(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT));

		VkDeviceMemory deviceMemory{};
		WLD_VkCheckError(vkAllocateMemory(m_Device, &allocInfo, nullptr, &deviceMemory));

		return deviceMemory;
	}

	void VulkanMemoryAllocator::DeallocateMemory(VkDeviceMemory deviceMemory) const
	{
		vkFreeMemory(m_Device, deviceMemory, nullptr);
	}

	uint32_t VulkanMemoryAllocator::GetMemoryTypeIndex(const uint32_t typeFilter, const VkMemoryPropertyFlags properties) const 
	{
		for (uint32_t i = 0; i < m_PhysicalDeviceMemoryProperties.memoryTypeCount; i++)
			if (typeFilter & BIT(i) && (m_PhysicalDeviceMemoryProperties.memoryTypes[i].propertyFlags & properties) == properties)
				return i;

		return INT32_MAX;
	}
}

