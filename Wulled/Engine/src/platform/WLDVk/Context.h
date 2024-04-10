#pragma once
#include "Engine/src/core/EngineCore.h"

#include "Engine/src/core/graphics/GraphicsContext.h"
/*
#include <vulkan/vulkan.h>


namespace WLD::Graphics::Vulkan
{
	class WLD_API VulkanContext : public GraphicsContext
	{
	public:
		VulkanContext(HWND* windowHandle, WindowProps& props);

		virtual void CreateDevice() override;
		virtual void Shutdown() override;
		virtual void SwapBuffers() override;
		virtual void OnWindowResize(uint32_t width, uint32_t height) override;
		virtual void MakeCurrent() override;

		virtual void Info() override;

	private:
		HWND* m_WindowHandle;
		HDC m_HDC;
		bool m_IsInitialized = false;

		VkInstance m_Instance;

// From https://harrylovescode.gitbooks.io/vulkan-api/content/chap05/chap05_0.html on 27/03/2024
		PFN_vkGetPhysicalDeviceSurfaceSupportKHR fpGetPhysicalDeviceSurfaceSupportKHR;
		PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR fpGetPhysicalDeviceSurfaceCapabilitiesKHR;
		PFN_vkGetPhysicalDeviceSurfaceFormatsKHR fpGetPhysicalDeviceSurfaceFormatsKHR;
		PFN_vkGetPhysicalDeviceSurfacePresentModesKHR fpGetPhysicalDeviceSurfacePresentModesKHR;
		PFN_vkCreateSwapchainKHR fpCreateSwapchainKHR;
		PFN_vkDestroySwapchainKHR fpDestroySwapchainKHR;
		PFN_vkGetSwapchainImagesKHR fpGetSwapchainImagesKHR;
		PFN_vkAcquireNextImageKHR fpAcquireNextImageKHR;
		PFN_vkQueuePresentKHR fpQueuePresentKHR;
// end From https://harrylovescode.gitbooks.io/vulkan-api/content/chap05/chap05_0.html on 27/03/2024
		
		static inline HGLRC s_hglrc;

		const WindowProps& m_WindowProps;
	};
}
*/