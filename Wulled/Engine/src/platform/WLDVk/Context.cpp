#include <WLDVk/Context.h>
/*
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.hpp>

#include "windows/Window.h"


// From https://harrylovescode.gitbooks.io/vulkan-api/content/chap05/chap05_0.html on 27/03/2024
#define GET_INSTANCE_PROC_ADDR(inst, entry)                              \
  {                                                                      \
    fp##entry = (PFN_vk##entry)vkGetInstanceProcAddr(inst, "vk" #entry); \
    if (!fp##entry)                                                      \
      exitOnError("vkGetInstanceProcAddr failed to find vk" #entry);     \
  }

#define GET_DEVICE_PROC_ADDR(dev, entry)                              \
  {                                                                   \
    fp##entry = (PFN_vk##entry)vkGetDeviceProcAddr(dev, "vk" #entry); \
    if (!fp##entry)                                                   \
      exitOnError("vkGetDeviceProcAddr failed to find vk" #entry);    \
  }
// end From https://harrylovescode.gitbooks.io/vulkan-api/content/chap05/chap05_0.html on 27/03/2024

namespace WLD::Graphics::Vulkan
{
	VulkanContext::VulkanContext(HWND* windowHandle, WindowProps& props)
		: m_WindowHandle(windowHandle), m_WindowProps(props)
	{
		WLD_CORE_ASSERT(windowHandle, "Window handle is null!");
		m_HDC = GetDC(*m_WindowHandle);
	}

	void VulkanContext::CreateDevice()
	{
		size_t outSize;
		char* windowNameC = CreateArray(char, wcslen(m_WindowProps.Title) + 1);
		wcstombs_s(&outSize, windowNameC, wcslen(m_WindowProps.Title) + 1, m_WindowProps.Title, wcslen(m_WindowProps.Title));

		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pNext = nullptr;
		appInfo.pApplicationName = windowNameC;

		VkWin32SurfaceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		createInfo.pNext = nullptr;
		createInfo.flags = NULL;
		createInfo.hinstance = GetModuleHandle(NULL);
		createInfo.hwnd = *m_WindowHandle;

		vkCreateInstance(&createInfo, nullptr, &m_Instance);

//		GET_INSTANCE_PROC_ADDR(vkCreateWin32SurfaceKHR);
// From https://harrylovescode.gitbooks.io/vulkan-api/content/chap05/chap05_0.html on 27/03/2024
		GET_INSTANCE_PROC_ADDR(m_Instance, GetPhysicalDeviceSurfaceSupportKHR);
		GET_INSTANCE_PROC_ADDR(m_Instance, GetPhysicalDeviceSurfaceCapabilitiesKHR);
		GET_INSTANCE_PROC_ADDR(m_Instance, GetPhysicalDeviceSurfaceFormatsKHR);
		GET_INSTANCE_PROC_ADDR(m_Instance, GetPhysicalDeviceSurfacePresentModesKHR);
		GET_DEVICE_PROC_ADDR(device, CreateSwapchainKHR);
//		GET_DEVICE_PROC_ADDR(device, DestroySwapchainKHR);
//		GET_DEVICE_PROC_ADDR(device, GetSwapchainImagesKHR);
//		GET_DEVICE_PROC_ADDR(device, AcquireNextImageKHR);
//		GET_DEVICE_PROC_ADDR(device, QueuePresentKHR);
// end From https://harrylovescode.gitbooks.io/vulkan-api/content/chap05/chap05_0.html on 27/03/2024
	}

	void VulkanContext::Shutdown()
	{
	}

	void VulkanContext::SwapBuffers()
	{
	}

	void VulkanContext::OnWindowResize(uint32_t width, uint32_t height)
	{
	}

	void VulkanContext::MakeCurrent()
	{
	}

	void VulkanContext::Info()
	{
	}
}
*/