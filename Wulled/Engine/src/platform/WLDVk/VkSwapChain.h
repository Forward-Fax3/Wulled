#pragma once
#include "Engine/src/Core/EngineCore.h"
#include "Engine/src/Core/Window.h"

#include <vulkan/vulkan.h>


namespace WLD
{
	class WLD_API VulkanContext;

	class WLD_API WLD_VkSwapChain
	{
	public:
		WLD_VkSwapChain(WindowProps& props, VulkanContext* vkContext, VkSurfaceKHR& surface, VkPhysicalDevice& physicalDevice, VkDevice& device);
		~WLD_VkSwapChain();

		VkFormat GetImageFormat() const { return ImageFormat; }

	private:
		void CreateSwapChain();
		void CreateImageViews();

		// private Helper Structs
	private:
		struct SwapChainSupportDetails
		{
			VkSurfaceCapabilitiesKHR capabilities = {};

			uint32_t NumberOfFormats = NULL;
			VkSurfaceFormatKHR* formats = nullptr;

			uint32_t NumberOfPresentModes = NULL;
			VkPresentModeKHR* presentModes = nullptr;
		};

		// private Helper Functions
	private:
		void CheckSwapChainSupport(SwapChainSupportDetails& details) const;
		void SetSwapChainAndPresentMode(const SwapChainSupportDetails& details, VkSurfaceFormatKHR& surfaceFormat, VkPresentModeKHR& presentMode) const;

		// private dataq
	private:
		WindowProps& m_WindowProps;
		VulkanContext& m_VkContext;

		VkSurfaceKHR& m_Surface;
		VkPhysicalDevice& m_PhysicalDevice;
		VkDevice& m_Device;

		VkSwapchainKHR SwapChain = VK_NULL_HANDLE;
		VkExtent2D ImageExtent = { NULL, NULL };
		VkFormat ImageFormat = VK_FORMAT_UNDEFINED;
		uint32_t NumberOfImages = NULL;
		VkImage* Images = nullptr;
		VkImageView* ImageViews = nullptr;
	};
}

#ifndef WLD_VKCONTEXT_H
#include "Engine/src/Platform/WLDVk/VkContext.h"
#endif
