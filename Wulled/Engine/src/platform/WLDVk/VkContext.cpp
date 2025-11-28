#include "wldpch.h"
#include "VkContext.h"
#include "VkErrors.h"
#include "WLDMem.h"

#include <vulkan/vulkan.h>

#include <SDL.h>
#include <SDL_vulkan.h>

#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_vulkan.h"

#include "VkMemoryAllocator.h"

namespace WLD
{
	VulkanContext* VulkanContext::s_Instance = nullptr;

	VulkanContext::VulkanContext(WindowProps& props)
		: GraphicsContext(props)
	{
		WLD_CORE_ASSERT(!s_Instance, "VulkanContext already exists!");
		s_Instance = this;

		m_WindowProps.Flags = static_cast<SDL_WindowFlags>(SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	}

	void VulkanContext::CreateDevice()
	{
		WLD_SDLCheckError(SDL_Vulkan_LoadLibrary(nullptr));

		CreateInstance();
		DebugMessagingSetup();
		CreateSurface();
		PickPhysicalDevice();
		CreateLogicalDevice();
		m_SwapChain = CreateMemory(WLD_VkSwapChain, m_WindowProps, *this, m_Surface, m_PhysicalDevice, m_Device);
		m_RenderPass = CreateMemory(RenderPass, *this);
		CreateFrameBuffers();

		const VulkanMemoryAllocator* vma = new VulkanMemoryAllocator(m_Device, m_PhysicalDevice); (void)*vma; // "use" vms to avoid variable not used errors
	}

	void VulkanContext::Shutdown()
	{
		delete VulkanMemoryAllocator::s_VkAllocator;

		DestroyMemory(m_RenderPass);
		DestroyMemory(m_SwapChain);
		vkDestroyDevice(m_Device, nullptr);
		vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);
		DebugMessengerShutdown();
		vkDestroyInstance(m_Instance, nullptr);
		SDL_Vulkan_UnloadLibrary();

		for (size_t i = m_NumberOfRequiredInstanceExtension; i < m_TotalNumberOfInstanceExtensions; i++)
			DestroyArray(m_InstanceExtensions[i]);

		for (size_t i = 0; i < m_NumberOfValidationLayers; i++)
			DestroyArray(m_ValidationLayers[i]);

		if (m_TotalNumberOfInstanceExtensions)
			DestroyArray(m_InstanceExtensions);
		if (m_NumberOfValidationLayers)
			DestroyArray(m_ValidationLayers);
	}

	void VulkanContext::SwapBuffers()
	{
		m_CurrentFrameBuffer++;

		if (m_CurrentFrameBuffer == 3)
			m_CurrentFrameBuffer = 0;
	}

	void VulkanContext::OnWindowResize()
	{
	}

	void VulkanContext::MakeCurrent() const
	{
	}

	void VulkanContext::SetVsync(const bool vsync)
	{
	}

	void VulkanContext::ImGuiInit() const
	{
		ImGui_ImplSDL2_InitForVulkan(m_WindowProps.SDLWindow);
		ImGui_ImplVulkan_InitInfo init_info = {};
		init_info.Instance = m_Instance;
		init_info.PhysicalDevice = m_PhysicalDevice;
		init_info.Device = m_Device;
//		init_info.QueueFamily = ;
//		init_info.Queue = g_Queue;
//		init_info.PipelineCache = g_PipelineCache;
//		init_info.DescriptorPool = ;
		init_info.Subpass = 0;
//		init_info.MinImageCount = g_MinImageCount;
//		init_info.ImageCount = wd->ImageCount;
		init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
#ifdef _DEBUG
		init_info.CheckVkResultFn = WLD_VkCheckError;
#endif
//		ImGui_ImplVulkan_Init(&init_info, wd->RenderPass);
	}

	void VulkanContext::ImGuiBegin() const
	{
//		ImGui_ImplVulkan_NewFrame();
	}

	void VulkanContext::ImGuiEnd() const
	{
//		ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), ::vk::CommandBuffer());
	}

	void VulkanContext::ImGuiShutdown() const
	{
//		ImGui_ImplVulkan_Shutdown();
	}

	void VulkanContext::Info()
	{
		VkPhysicalDeviceProperties deviceProperties;
		vkGetPhysicalDeviceProperties(m_PhysicalDevice, &deviceProperties);
		LOG_CORE_INFO("Vulkan Device: {0}", deviceProperties.deviceName);
	}

	void VulkanContext::CreateInstance()
	{
		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = m_WindowProps.TitleC;
		appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
		appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
		appInfo.pEngineName = "Wulled";
		appInfo.apiVersion = VK_API_VERSION_1_3;

#ifndef _DIST
		m_NumberOfValidationLayers = 1;
		m_ValidationLayers = CreateArray(const char*, m_NumberOfValidationLayers);
		const char* validationLayers[] = {"VK_LAYER_KHRONOS_validation"};

		const char* debugUtils[] = { VK_EXT_DEBUG_UTILS_EXTENSION_NAME };
		uint32_t numberOfDebugUtils = 1;

		m_DebugMessengerCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		m_DebugMessengerCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		m_DebugMessengerCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		m_DebugMessengerCreateInfo.pfnUserCallback = VulkanContext::StaticDebugCallback;
		m_DebugMessengerCreateInfo.pUserData = nullptr;
#else
		const char* validationLayers[] = { nullptr };
		uint32_t m_NumberOfValidationLayers = 0;
		const char* debugUtils[] = { nullptr };
		uint32_t numberOfDebugUtils = 0;
#endif
		WLD_SDLCheckError(SDL_Vulkan_GetInstanceExtensions(m_WindowProps.SDLWindow, &m_NumberOfRequiredInstanceExtension, nullptr));
		m_InstanceExtensions = CreateArray(const char*, m_NumberOfRequiredInstanceExtension + numberOfDebugUtils);
		WLD_SDLCheckError(SDL_Vulkan_GetInstanceExtensions(m_WindowProps.SDLWindow, &m_NumberOfRequiredInstanceExtension, m_InstanceExtensions));

		for (size_t i = 0; i < numberOfDebugUtils; i++)
		{
			char* debugUtil = CreateArray(char, strlen(debugUtils[i]) + 1);
			strcpy(debugUtil, debugUtils[i]);
			m_InstanceExtensions[m_NumberOfRequiredInstanceExtension + i] = debugUtil;
		}
		m_TotalNumberOfInstanceExtensions = m_NumberOfRequiredInstanceExtension + numberOfDebugUtils;

		for (size_t i = 0; i < m_NumberOfValidationLayers; i++)
		{
			char* validationLayer = CreateArray(char, strlen(validationLayers[i]) + 1);
			strcpy(validationLayer, validationLayers[i]);
			m_ValidationLayers[i] = validationLayer;
		}

		// TODO: Check if that requested layers are available
		// TODO: Check if that requested extensions are available

		VkInstanceCreateInfo InstanceInfo = {};
		InstanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		InstanceInfo.pApplicationInfo = &appInfo;
		InstanceInfo.enabledExtensionCount = m_TotalNumberOfInstanceExtensions;
		InstanceInfo.ppEnabledExtensionNames = m_InstanceExtensions;
		InstanceInfo.enabledLayerCount = m_NumberOfValidationLayers;
		InstanceInfo.ppEnabledLayerNames = m_ValidationLayers;

#ifndef _DIST
		InstanceInfo.pNext = &m_DebugMessengerCreateInfo;
#endif

		WLD_VkCheckError(vkCreateInstance(&InstanceInfo, nullptr, &m_Instance));
	}

	void VulkanContext::DebugMessagingSetup()
	{
#if !defined(_DIST)
		const PFN_vkCreateDebugUtilsMessengerEXT func = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(m_Instance, "vkCreateDebugUtilsMessengerEXT"));
		WLD_CORE_ASSERT(func, "Failed to get vkCreateDebugUtilsMessengerEXT");
		WLD_VkCheckError(func(m_Instance, &m_DebugMessengerCreateInfo, nullptr, &m_DebugMessenger));
#endif
	}

	void VulkanContext::CreateSurface()
	{
		WLD_SDLCheckError(SDL_Vulkan_CreateSurface(m_WindowProps.SDLWindow, m_Instance, &m_Surface));
	}

	void VulkanContext::PickPhysicalDevice()
	{
		uint32_t numberOfPhysicalDevices = 0;
		WLD_VkCheckError(vkEnumeratePhysicalDevices(m_Instance, &numberOfPhysicalDevices, nullptr));
		VkPhysicalDevice* physicalDevices = CreateArray(VkPhysicalDevice, numberOfPhysicalDevices);
		WLD_VkCheckError(vkEnumeratePhysicalDevices(m_Instance, &numberOfPhysicalDevices, physicalDevices));

		for (uint32_t i = 0; i < numberOfPhysicalDevices; i++)
		{
			VkPhysicalDeviceProperties deviceProperties;
			vkGetPhysicalDeviceProperties(physicalDevices[i], &deviceProperties);
			if (deviceProperties.deviceType != VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && numberOfPhysicalDevices > 1)
				continue;

			if (deviceProperties.apiVersion < VK_API_VERSION_1_3)
				continue;

			VkPhysicalDeviceFeatures deviceFeatures;
			vkGetPhysicalDeviceFeatures(physicalDevices[i], &deviceFeatures);

			if (!deviceFeatures.geometryShader)
				continue;

			if (!deviceFeatures.samplerAnisotropy)
				continue;

			m_PhysicalDevice = physicalDevices[i];
			break;
		}
		DestroyArray(physicalDevices);

		WLD_CORE_ASSERT(m_PhysicalDevice, "Failed to find a suitable GPU!");
	} // TODO: make a more complex device selection to get the best device

	void VulkanContext::CreateLogicalDevice()
	{
		constexpr float queuePriority = 1.0f;
		VkDeviceQueueCreateInfo queueInfos[] = { {}, {} };
		uint32_t* queues = nullptr;
		const uint32_t numberOfQueues = GetQueueFamilies(queues);

		for (size_t i = 0; i < numberOfQueues; i++)
		{
			queueInfos[i].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueInfos[i].queueFamilyIndex = queues[i];
			queueInfos[i].queueCount = 1;
			queueInfos[i].pQueuePriorities = &queuePriority;
		}

		VkPhysicalDeviceFeatures deviceFeatures = {};
		const char* deviceExtensions[] = { "VK_KHR_swapchain" };
		VkDeviceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.queueCreateInfoCount = 2;
		createInfo.pQueueCreateInfos = queueInfos;
		createInfo.enabledExtensionCount = 1;
		createInfo.ppEnabledExtensionNames = deviceExtensions;
		createInfo.pEnabledFeatures = &deviceFeatures;

		WLD_VkCheckError(vkCreateDevice(m_PhysicalDevice, &createInfo, nullptr, &m_Device));

		vkGetDeviceQueue(m_Device, queues[0], 0, &m_QueueFamilies.Graphics);
		vkGetDeviceQueue(m_Device, queues[1], 0, &m_QueueFamilies.Present);

		DestroyArray(queues);
	}

	void VulkanContext::CreateFrameBuffers()
	{
		m_FrameBuffers = CreateArray(VkFramebuffer, m_SwapChain->m_NumberOfImages);

		for (uint32_t i = 0; i < m_SwapChain->m_NumberOfImages; i++)
		{
			VkFramebufferCreateInfo framebufferInfo{};
			framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebufferInfo.renderPass = m_RenderPass->GetRenderPass();
			framebufferInfo.attachmentCount = 1;
			framebufferInfo.pAttachments = &m_SwapChain->m_ImageViews[i];
			framebufferInfo.width = m_WindowProps.Width;
			framebufferInfo.height = m_WindowProps.Height;
			framebufferInfo.layers = 1;

			WLD_VkCheckError(vkCreateFramebuffer(m_Device, &framebufferInfo, nullptr, &m_FrameBuffers[i]));
		}
	}

	void VulkanContext::DebugMessengerShutdown() const
	{
#ifndef _DIST
		const PFN_vkDestroyDebugUtilsMessengerEXT func = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(m_Instance, "vkDestroyDebugUtilsMessengerEXT"));
		WLD_CORE_ASSERT(func, "Failed to get vkDestroyDebugUtilsMessengerEXT");
		func(m_Instance, m_DebugMessenger, nullptr);
#endif
	}

	uint32_t VulkanContext::GetQueueFamilies(uint32_t*& queues) const
	{
		uint32_t numberOfQueueFamilies = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(m_PhysicalDevice, &numberOfQueueFamilies, nullptr);
		VkQueueFamilyProperties* queueFamilies = CreateArray(VkQueueFamilyProperties, numberOfQueueFamilies);
		vkGetPhysicalDeviceQueueFamilyProperties(m_PhysicalDevice, &numberOfQueueFamilies, queueFamilies);
		uint32_t graphicsQueueFamily = UINT32_MAX, presentQueueFamily = UINT32_MAX;

		for (uint32_t i = 0; i < numberOfQueueFamilies; i++)
		{
			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(m_PhysicalDevice, i, m_Surface, &presentSupport);

			if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
				graphicsQueueFamily = i;

			else if (presentSupport)
				presentQueueFamily = i;

			if (graphicsQueueFamily != UINT32_MAX && presentQueueFamily != UINT32_MAX)
				break;
		}
		DestroyArray(queueFamilies);

		constexpr uint32_t numberOfQueues = 2;
		queues = CreateArray(uint32_t, numberOfQueues);
		queues[0] = graphicsQueueFamily;
		queues[1] = presentQueueFamily;
		return numberOfQueues;
	}

	VkBool32 VulkanContext::StaticDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
	{
		return s_Instance->DebugCallback(messageSeverity, messageType, pCallbackData, pUserData);
	}

	VkBool32 VulkanContext::DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) const
	{
		if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
			LOG_CORE_CRITICAL("Vulkan Call Back: {0}", pCallbackData->pMessage);
		else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
			LOG_CORE_WARNING("Vulkan Call Back: {0}", pCallbackData->pMessage);
		else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
			LOG_CORE_INFO("Vulkan Call Back: {0}", pCallbackData->pMessage);
		else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT)
			LOG_CORE_TRACE("Vulkan Call Back: {0}", pCallbackData->pMessage);
		else
			LOG_CORE_ERROR("Unknown Vulkan Call Back: {0}", pCallbackData->pMessage);

		return VK_FALSE;
	};
}