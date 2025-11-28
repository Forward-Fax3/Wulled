#pragma once
#define WLD_VKCONTEXT_H

#include "EngineCore.h"

#include "Window.h"
#include "GraphicsContext.h"
#include "VkSwapChain.h"
#include "VkRendererAPI.h"
#include "RenderPass.h"

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
		virtual void MakeCurrent() const override;
		virtual void SetVsync(const bool vsync) override;
		virtual void ImGuiInit() const override;
		virtual void ImGuiBegin() const override;
		virtual void ImGuiEnd() const override;
		virtual void ImGuiShutdown() const override;

		virtual void Info() override;

		inline VkDevice GetDevice() const { return m_Device; }
		inline VkRenderPass GetRenderPass() const { return m_RenderPass->GetRenderPass(); }
		inline void BeginRenderPass(const VkClearValue& clearValue) const { m_RenderPass->BeginRenderPass(m_CommandBuffer, clearValue); }
		inline void EndRenderPass() const { m_RenderPass->EndRenderPass(); }
		inline WLD_VkSwapChain& GetSwapChain() const { return *m_SwapChain; }
		inline VkFramebuffer& GetFrameBuffer() const { return m_FrameBuffers[m_CurrentFrameBuffer]; }

		inline void SetCommandBuffer(VkCommandBuffer commandBuffer) { m_CommandBuffer = commandBuffer; }
		inline const VkCommandBuffer GetCommandBuffer() const { return m_CommandBuffer; }

	private: // Helper Functions
		void CreateInstance();
		void DebugMessagingSetup();
		void CreateSurface();
		void PickPhysicalDevice();
		void CreateLogicalDevice();
		void CreateFrameBuffers();

		void DebugMessengerShutdown() const;

		uint32_t GetQueueFamilies(uint32_t*& queues) const;

		static VkBool32 StaticDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
		VkBool32 DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) const;

	private: // data
		VkInstance m_Instance = VK_NULL_HANDLE;
		VkSurfaceKHR m_Surface = VK_NULL_HANDLE;
		VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
		VkDevice m_Device = VK_NULL_HANDLE;

		VkFramebuffer* m_FrameBuffers = nullptr;
		size_t m_CurrentFrameBuffer = 0;

		WLD_VkSwapChain* m_SwapChain = nullptr;
		RenderPass* m_RenderPass = nullptr;

		VkCommandBuffer m_CommandBuffer = nullptr;
		
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
		friend class ::WLD::VulkanRendererAPI;
	};
}
