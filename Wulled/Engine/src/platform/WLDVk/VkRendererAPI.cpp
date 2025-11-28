#include "wldpch.h"
#include "VkRendererAPI.h"
#include "VkErrors.h"

#include "application.h"
#include "VkContext.h"
#include "VkVertexArray.h"
#include "Renderer.h"


namespace WLD
{
	VulkanRendererAPI::~VulkanRendererAPI()
	{
		const VulkanContext& vkContext = dynamic_cast<const VulkanContext&>(Application::Get().GetWindow().GetGraphicsContext());
		vkDestroyCommandPool(vkContext.GetDevice(), m_CommandPool, nullptr);
	}

	void VulkanRendererAPI::Init()
	{
		const VulkanContext& vkContext = dynamic_cast<const VulkanContext&>(Application::Get().GetWindow().GetGraphicsContext());
		uint32_t* queueFamilies;
		vkContext.GetQueueFamilies(queueFamilies);
		
		VkCommandPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		poolInfo.queueFamilyIndex = queueFamilies[0];

		WLD_VkCheckError(vkCreateCommandPool(vkContext.GetDevice(), &poolInfo, nullptr, &m_CommandPool));

		VkCommandBufferAllocateInfo bufferAllocateInfo{};
		bufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		bufferAllocateInfo.commandPool = m_CommandPool;
		bufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		bufferAllocateInfo.commandBufferCount = 1;

		WLD_VkCheckError(vkAllocateCommandBuffers(vkContext.GetDevice(), &bufferAllocateInfo, &m_CommnadBuffer));

		// removes the const label so it can set the command buffer
		const_cast<VulkanContext&>(vkContext).SetCommandBuffer(m_CommnadBuffer);
	}

	void VulkanRendererAPI::Clear()
	{
		const glm::vec4& colour = Renderer::GetBackgroundColour();
		m_ClearValue.color.float32[0] = colour.r;
		m_ClearValue.color.float32[1] = colour.g;
		m_ClearValue.color.float32[2] = colour.b;
		m_ClearValue.color.float32[3] = colour.a;

		m_ClearValue.depthStencil.depth = 0.0f;
		m_ClearValue.depthStencil.stencil = 0;
	}

	void VulkanRendererAPI::BeginScene()
	{
		const Window& window = Application::Get().GetWindow();
		const VulkanContext& vkContext = dynamic_cast<const VulkanContext&>(window.GetGraphicsContext());

		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = 0;
		beginInfo.pInheritanceInfo = nullptr;
		WLD_VkCheckError(vkBeginCommandBuffer(m_CommnadBuffer, &beginInfo));

		vkContext.BeginRenderPass(m_ClearValue);

		VkViewport veiwport{};
		veiwport.x = 0;
		veiwport.y = 0;
		veiwport.width = static_cast<float>(vkContext.GetSwapChain().GetSwapChainExtent2D().width);
		veiwport.height = static_cast<float>(vkContext.GetSwapChain().GetSwapChainExtent2D().height);
		veiwport.minDepth = 0.0f;
		veiwport.maxDepth = 1.0f;
		vkCmdSetViewport(m_CommnadBuffer, 0, 1, &veiwport);

		VkRect2D scissor{};
		scissor.offset = { 0, 0 };
		scissor.extent = vkContext.GetSwapChain().GetSwapChainExtent2D();
		vkCmdSetScissor(m_CommnadBuffer, 0, 1, &scissor);
	}

	void VulkanRendererAPI::EndScene()
	{
		dynamic_cast<const VulkanContext&>(Application::Get().GetWindow().GetGraphicsContext()).EndRenderPass();
		WLD_VkCheckError(vkEndCommandBuffer(m_CommnadBuffer));
	}

	void VulkanRendererAPI::DrawIndexed(const Ref<VertexArray> vertexArray)
	{
//		vertexArray->Bind();
//		vertexArray->GetIndexBuffer()->Bind();

		// using this instead of Ref as Ref doesn't want to cast a parent class to a child class for some reason.
		const VulkanVertexArray* vkVertexArray = dynamic_cast<const VulkanVertexArray*>(vertexArray.get());

		vkVertexArray->Bind(m_CommnadBuffer);

		vkCmdDrawIndexed(m_CommnadBuffer, static_cast<uint32_t>(vertexArray->GetVertexBuffers().size()), 1, 0, 0, 0);
		WLD_VkCheckError(vkCmdEndRenderPass(m_CommnadBuffer));
	}
} 
