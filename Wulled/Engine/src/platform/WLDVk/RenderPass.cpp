#include "wldpch.h"
#include "RenderPass.h"
#include "application.h"
#include "VkContext.h"
#include "VkErrors.h"


namespace WLD
{
	RenderPass::RenderPass(const VulkanContext& context)
	{
		VkAttachmentDescription colorAttachment = {};
		colorAttachment.format = context.GetSwapChain().GetImageFormat();
		colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
		colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		VkAttachmentReference colorAttachmentRef = {};
		colorAttachmentRef.attachment = 0;
		colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkSubpassDescription subpass = {};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &colorAttachmentRef;

		VkRenderPassCreateInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassInfo.attachmentCount = 1;
		renderPassInfo.pAttachments = &colorAttachment;
		renderPassInfo.subpassCount = 1;
		renderPassInfo.pSubpasses = &subpass;

		WLD_VkCheckError(vkCreateRenderPass(context.GetDevice(), &renderPassInfo, nullptr, &m_RenderPass));
	}

	RenderPass::~RenderPass()
	{
		const VulkanContext& context = dynamic_cast<const VulkanContext&>(Application::Get().GetWindow().GetGraphicsContext());
		vkDestroyRenderPass(context.GetDevice(), m_RenderPass, nullptr);
	}

	void RenderPass::BeginRenderPass(VkCommandBuffer commandBuffer, const VkClearValue& clearValue)
	{
		const VulkanContext& vkContext = dynamic_cast<const VulkanContext&>(Application::Get().GetWindow().GetGraphicsContext());

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = vkContext.GetRenderPass();
		renderPassInfo.framebuffer = vkContext.GetFrameBuffer();
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = vkContext.GetSwapChain().GetSwapChainExtent2D();
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearValue;

		vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
	}

	void RenderPass::EndRenderPass()
	{

	}

}
