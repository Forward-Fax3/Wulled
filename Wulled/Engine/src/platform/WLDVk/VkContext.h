#pragma once
#define WLD_VKCONTEXT_H

#include "Engine/src/core/EngineCore.h"

#include "Engine/src/core/Window.h"
#include "Engine/src/core/graphics/GraphicsContext.h"
#include "Engine/src/platform/WLDVk/VkSwapChain.h"

#include <vulkan/vulkan.h>


namespace WLD
{
	class WLD_API VulkanContext : public GraphicsContext
	{
	public:
		VulkanContext(WindowProps& props);

		virtual void CreateDevice() override;
		virtual void Shutdown() override;
		virtual void SwapBuffers() override;
		virtual void OnWindowResize() override;
		virtual void MakeCurrent() override;
		virtual void SetVsync(const bool vsync) override;
		virtual void ImGuiInit() override;
		virtual void ImGuiBegin() override;
		virtual void ImGuiEnd() override;
		virtual void ImGuiShutdown() override;

		virtual void Info() override;

		VkDevice GetDevice() const { return m_Device; }
		WLD_VkSwapChain& GetSwapChain() const { return *m_SwapChain; }

	// private Helper Functions
	private:
		void CreateInstance();
		void DubugMessengingSetup();
		void CreateSurface();
		void PickPhysicalDevice();
		void CreateLogicalDevice();

		void DebugMessengerShutdown() const;

		uint32_t GetQueueFamilies(uint32_t*& queues) const;

		static VkBool32 StaticDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
		VkBool32 DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) const;

	// private data
	private:
		VkInstance m_Instance = VK_NULL_HANDLE;
		VkSurfaceKHR m_Surface = VK_NULL_HANDLE;
		VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
		VkDevice m_Device = VK_NULL_HANDLE;
		VkRenderPass m_RenderPass = VK_NULL_HANDLE;

		WLD_VkSwapChain* m_SwapChain = nullptr;

		struct {
			VkQueue Graphics = VK_NULL_HANDLE;
			VkQueue Present = VK_NULL_HANDLE;
		} m_QueueFamilies;

		const char** m_InstanceExtensions = nullptr;
		uint32_t m_TotalNumberOfInstanceExtensions = NULL;
		uint32_t m_NumberOfRequiredInstanceExtension = NULL;
		const char** m_ValidationLayers = nullptr;
		uint32_t m_NumberOfValidationLayers = NULL;

#ifndef _DIST
		VkDebugUtilsMessengerEXT m_DebugMessenger = nullptr;
		VkDebugUtilsMessengerCreateInfoEXT m_DebugMessengerCreateInfo = {};
#endif

		static VulkanContext* s_Instance;

		friend class ::WLD::WLD_VkSwapChain;
	};
}
