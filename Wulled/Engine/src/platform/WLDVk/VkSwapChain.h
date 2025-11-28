#pragma once
#include "Engine/src/core/EngineCore.h"
#include "Engine/src/core/Window.h"

#include <vulkan/vulkan.h>


namespace WLD
{
	class WLD_API VulkanContext;

	class WLD_API WLD_VkSwapChain
	{
	public:
		WLD_VkSwapChain(const WindowProps& props, const VulkanContext& vkContext, const VkSurfaceKHR& surface, const VkPhysicalDevice& physicalDevice, const VkDevice& device);
		~WLD_VkSwapChain();

		inline VkFormat GetImageFormat() const { return m_ImageFormat; }
		inline VkExtent2D GetSwapChainExtent2D() const { return m_ImageExtent; }

	private:
		void CreateSwapChain();
		void CreateImageViews();

		// private Helper Struct
	private:
		struct SwapChainSupportDetails
		{
			VkSurfaceCapabilitiesKHR capabilities = {};

			uint32_t numberOfFormats = NULL;
			VkSurfaceFormatKHR* formats = nullptr;

			uint32_t numberOfPresentModes = NULL;
			VkPresentModeKHR* presentModes = nullptr;
		};

		// private Helper Functions
	private:
		void CheckSwapChainSupport(SwapChainSupportDetails& details) const;
		void SetSwapChainAndPresentMode(const SwapChainSupportDetails& details, VkSurfaceFormatKHR& surfaceFormat, VkPresentModeKHR& presentMode) const;

		// private data
	private:
		const WindowProps& m_WindowProps;
		const VulkanContext& m_VkContext;

		const VkSurfaceKHR& m_Surface;
		const VkPhysicalDevice& m_PhysicalDevice;
		const VkDevice& m_Device;

		VkSwapchainKHR m_SwapChain = VK_NULL_HANDLE;
		VkExtent2D m_ImageExtent = { NULL, NULL };
		VkFormat m_ImageFormat = VK_FORMAT_UNDEFINED;
		uint32_t m_NumberOfImages = NULL;
		VkImage* m_Images = nullptr;
		VkImageView* m_ImageViews = nullptr;

		// friend func/classes
	private:
		friend class VulkanContext;
	};
}

#ifndef WLD_VKCONTEXT_H
#include "Engine/src/platform/WLDVk/VkContext.h"
#endif
