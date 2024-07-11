#include "WLDPCH.h"
#include "UniformBuffer.h"
#include "Renderer.h"

#include "OpenGLUniformBuffer.h"
#include "VkUniformBuffer.h"


namespace WLD
{
    Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:    WLD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL:  return CreateRef(OpenGLUniformBuffer, size, binding);
        case RendererAPI::API::Vulkan:  return CreateRef(VkUniformBuffer, size, binding);
        default: WLD_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
        }
    }
}
