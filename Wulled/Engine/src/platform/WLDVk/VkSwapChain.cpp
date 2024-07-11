#include "WLDPCH.h"
#include "VkSwapChain.h"
#include "VkContext.h"
#include "VkErrors.h"

#include "WLDMem.h"


namespace WLD
{
	WLD_VkSwapChain::WLD_VkSwapChain(WindowProps& props, VulkanContext* vkContext, VkSurfaceKHR& surface, VkPhysicalDevice& physicalDevice, VkDevice& device)
		: m_WindowProps(props), m_VkContext(*vkContext), m_Surface(surface), m_PhysicalDevice(physicalDevice), m_Device(device)
	{
		CreateSwapChain();
		CreateImageViews();
	}

	WLD_VkSwapChain::~WLD_VkSwapChain()
	{
		for (size_t i = 0; i < NumberOfImages; i++)
			vkDestroyImageView(m_Device, ImageViews[i], nullptr);
		DestroyArray(ImageViews);

		vkDestroySwapchainKHR(m_Device, SwapChain, nullptr);
		DestroyArray(Images);
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

		ImageExtent = { m_WindowProps.Width, m_WindowProps.Height };

		NumberOfImages = swapChainSupport.capabilities.minImageCount + 1;
		if (NumberOfImages > swapChainSupport.capabilities.maxImageCount)
			NumberOfImages = swapChainSupport.capabilities.maxImageCount;

		VkSwapchainCreateInfoKHR createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = m_Surface;
		createInfo.minImageCount = NumberOfImages;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = ImageExtent;
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

		WLD_VkCheckError(vkCreateSwapchainKHR(m_Device, &createInfo, nullptr, &SwapChain));
		DestroyArray(queues);

		vkGetSwapchainImagesKHR(m_Device, SwapChain, &NumberOfImages, nullptr);
		Images = CreateArray(VkImage, NumberOfImages);
		vkGetSwapchainImagesKHR(m_Device, SwapChain, &NumberOfImages, Images);

		ImageFormat = surfaceFormat.format;
	}

	void WLD_VkSwapChain::CreateImageViews()
	{
		ImageViews = CreateArray(VkImageView, NumberOfImages);
		for (size_t i = 0; i < NumberOfImages; i++)
		{
			VkImageViewCreateInfo createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			createInfo.image = Images[i];
			createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			createInfo.format = ImageFormat;
			createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			createInfo.subresourceRange.baseMipLevel = 0;
			createInfo.subresourceRange.levelCount = 1;
			createInfo.subresourceRange.baseArrayLayer = 0;
			createInfo.subresourceRange.layerCount = 1;

			WLD_VkCheckError(vkCreateImageView(m_Device, &createInfo, nullptr, &ImageViews[i]));
		}
	}

	void WLD_VkSwapChain::CheckSwapChainSupport(SwapChainSupportDetails& swapChainSupport) const
	{
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_PhysicalDevice, m_Surface, &swapChainSupport.capabilities);

		vkGetPhysicalDeviceSurfaceFormatsKHR(m_PhysicalDevice, m_Surface, &swapChainSupport.NumberOfFormats, nullptr);
		WLD_CORE_ASSERT(swapChainSupport.NumberOfFormats, "Failed to get surface formats");
		swapChainSupport.formats = CreateArray(VkSurfaceFormatKHR, swapChainSupport.NumberOfFormats);
		vkGetPhysicalDeviceSurfaceFormatsKHR(m_PhysicalDevice, m_Surface, &swapChainSupport.NumberOfFormats, swapChainSupport.formats);

		vkGetPhysicalDeviceSurfacePresentModesKHR(m_PhysicalDevice, m_Surface, &swapChainSupport.NumberOfPresentModes, nullptr);
		WLD_CORE_ASSERT(swapChainSupport.NumberOfPresentModes, "Failed to get surface present modes");
		swapChainSupport.presentModes = CreateArray(VkPresentModeKHR, swapChainSupport.NumberOfPresentModes);
		vkGetPhysicalDeviceSurfacePresentModesKHR(m_PhysicalDevice, m_Surface, &swapChainSupport.NumberOfPresentModes, swapChainSupport.presentModes);
	}

	void WLD_VkSwapChain::SetSwapChainAndPresentMode(const SwapChainSupportDetails& swapChainSupport, VkSurfaceFormatKHR& surfaceFormat, VkPresentModeKHR& presentMode) const
	{
		for (uint32_t i = 0; i < swapChainSupport.NumberOfFormats; i++)
			if (swapChainSupport.formats[i].format == VK_FORMAT_B8G8R8A8_SRGB && swapChainSupport.formats[i].colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
			{
				surfaceFormat = swapChainSupport.formats[i];
				break;
			}

		if (surfaceFormat.format == VK_FORMAT_UNDEFINED)
			surfaceFormat = swapChainSupport.formats[0];

		for (uint32_t i = 0; i < swapChainSupport.NumberOfPresentModes; i++)
			if (swapChainSupport.presentModes[i] == VK_PRESENT_MODE_MAILBOX_KHR)
			{
				presentMode = swapChainSupport.presentModes[i];
				break;
			}
	}
}