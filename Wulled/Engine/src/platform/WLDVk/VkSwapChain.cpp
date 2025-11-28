#include "wldpch.h"
#include "VkSwapChain.h"
#include "VkContext.h"
#include "VkErrors.h"

#include "WLDMem.h"


namespace WLD
{
	WLD_VkSwapChain::WLD_VkSwapChain(const WindowProps& props, const VulkanContext& vkContext, const VkSurfaceKHR& surface, const VkPhysicalDevice& physicalDevice, const VkDevice& device)
		: m_WindowProps(props), m_VkContext(vkContext), m_Surface(surface), m_PhysicalDevice(physicalDevice), m_Device(device)
	{
		CreateSwapChain();
		CreateImageViews();
	}

	WLD_VkSwapChain::~WLD_VkSwapChain()
	{
		for (size_t i = 0; i < m_NumberOfImages; i++)
			vkDestroyImageView(m_Device, m_ImageViews[i], nullptr);
		DestroyArray(m_ImageViews);

		vkDestroySwapchainKHR(m_Device, m_SwapChain, nullptr);
		DestroyArray(m_Images);
	}

	void WLD_VkSwapChain::CreateSwapChain()
	{
		SwapChainSupportDetails swapChainSupport;
		VkSurfaceFormatKHR surfaceFormat = {};
		VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR;

		CheckSwapChainSupport(swapChainSupport);
		SetSwapChainAndPresentMode(swapChainSupport, surfaceFormat, presentMode);

		DestroyArray(swapChainSupport.formats);
		DestroyArray(swapChainSupport.presentModes);

		m_ImageExtent = { m_WindowProps.Width, m_WindowProps.Height };

		m_NumberOfImages = swapChainSupport.capabilities.minImageCount + 1;
		if (m_NumberOfImages > swapChainSupport.capabilities.maxImageCount)
			m_NumberOfImages = swapChainSupport.capabilities.maxImageCount;

		VkSwapchainCreateInfoKHR createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = m_Surface;
		createInfo.minImageCount = m_NumberOfImages;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = m_ImageExtent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;

		uint32_t* queues = nullptr;
		uint32_t numberOfQueues = m_VkContext.GetQueueFamilies(queues);

		if (queues[0] != queues[1])
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = numberOfQueues;
			createInfo.pQueueFamilyIndices = queues;
		}
		else
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			createInfo.queueFamilyIndexCount = 0;
			createInfo.pQueueFamilyIndices = nullptr;
		}

		WLD_VkCheckError(vkCreateSwapchainKHR(m_Device, &createInfo, nullptr, &m_SwapChain));
		DestroyArray(queues);

		vkGetSwapchainImagesKHR(m_Device, m_SwapChain, &m_NumberOfImages, nullptr);
		m_Images = CreateArray(VkImage, m_NumberOfImages);
		vkGetSwapchainImagesKHR(m_Device, m_SwapChain, &m_NumberOfImages, m_Images);

		m_ImageFormat = surfaceFormat.format;
	}

	void WLD_VkSwapChain::CreateImageViews()
	{
		m_ImageViews = CreateArray(VkImageView, m_NumberOfImages);
		for (size_t i = 0; i < m_NumberOfImages; i++)
		{
			VkImageViewCreateInfo createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			createInfo.image = m_Images[i];
			createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			createInfo.format = m_ImageFormat;
			createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			createInfo.subresourceRange.baseMipLevel = 0;
			createInfo.subresourceRange.levelCount = 1;
			createInfo.subresourceRange.baseArrayLayer = 0;
			createInfo.subresourceRange.layerCount = 1;

			WLD_VkCheckError(vkCreateImageView(m_Device, &createInfo, nullptr, &m_ImageViews[i]));
		}
	}

	void WLD_VkSwapChain::CheckSwapChainSupport(SwapChainSupportDetails& swapChainSupport) const
	{
		WLD_VkCheckError(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_PhysicalDevice, m_Surface, &swapChainSupport.capabilities));

		WLD_VkCheckError(vkGetPhysicalDeviceSurfaceFormatsKHR(m_PhysicalDevice, m_Surface, &swapChainSupport.numberOfFormats, nullptr));
		WLD_CORE_ASSERT(swapChainSupport.numberOfFormats, "Failed to get surface formats");
		swapChainSupport.formats = CreateArray(VkSurfaceFormatKHR, swapChainSupport.numberOfFormats);
		WLD_VkCheckError(vkGetPhysicalDeviceSurfaceFormatsKHR(m_PhysicalDevice, m_Surface, &swapChainSupport.numberOfFormats, swapChainSupport.formats));

		WLD_VkCheckError(vkGetPhysicalDeviceSurfacePresentModesKHR(m_PhysicalDevice, m_Surface, &swapChainSupport.numberOfPresentModes, nullptr));
		WLD_CORE_ASSERT(swapChainSupport.numberOfPresentModes, "Failed to get surface present modes");
		swapChainSupport.presentModes = CreateArray(VkPresentModeKHR, swapChainSupport.numberOfPresentModes);
		WLD_VkCheckError(vkGetPhysicalDeviceSurfacePresentModesKHR(m_PhysicalDevice, m_Surface, &swapChainSupport.numberOfPresentModes, swapChainSupport.presentModes));
	}

	void WLD_VkSwapChain::SetSwapChainAndPresentMode(const SwapChainSupportDetails& swapChainSupport, VkSurfaceFormatKHR& surfaceFormat, VkPresentModeKHR& presentMode) const
	{
		for (uint32_t i = 0; i < swapChainSupport.numberOfFormats; i++)
			if (swapChainSupport.formats[i].format == VK_FORMAT_B8G8R8A8_SRGB && swapChainSupport.formats[i].colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
			{
				surfaceFormat = swapChainSupport.formats[i];
				break;
			}

		if (surfaceFormat.format == VK_FORMAT_UNDEFINED)
			surfaceFormat = swapChainSupport.formats[0];

		for (uint32_t i = 0; i < swapChainSupport.numberOfPresentModes; i++)
			if (swapChainSupport.presentModes[i] == VK_PRESENT_MODE_MAILBOX_KHR)
			{
				presentMode = swapChainSupport.presentModes[i];
				break;
			}
	}
}