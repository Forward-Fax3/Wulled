#include "WLDPCH.h"
#include "Log.h"
#include "EngineCore.h"

#include "Renderer.h"
#include "Buffer.h"
#include "OpenGLBuffer.h"

#include "WLDMem.h"


namespace WLD
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: WLD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateMemory(OpenGLVertexBuffer, vertices, size);
//		case RendererAPI::API::Vulkan: return createMemory(VulkanVertexBuffer, vertices, size);

		default: WLD_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
		}
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: WLD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateMemory(OpenGLIndexBuffer, indices, size);
//		case RendererAPI::API::Vulkan: return createMemory(VulkanIndexBuffer, indices, size);

		default: WLD_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
		}
	}

	uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::None:		LOG_CORE_WARNING("shader type is none my not work"); return 0;
		case ShaderDataType::Bool:		return 1;
		case ShaderDataType::Int:		return 4 * 1;
		case ShaderDataType::Int2:		return 4 * 2;
		case ShaderDataType::Int3:		return 4 * 3;
		case ShaderDataType::Int4:		return 4 * 4;
		case ShaderDataType::Float:		return 4 * 1;
		case ShaderDataType::Float2:	return 4 * 2;
		case ShaderDataType::Float3:	return 4 * 3;
		case ShaderDataType::Float4:	return 4 * 4;
		case ShaderDataType::Mat2x2:	return 4 * 2 * 2;
		case ShaderDataType::Mat2x3:	return 4 * 2 * 3;
		case ShaderDataType::Mat2x4:	return 4 * 2 * 4;
		case ShaderDataType::Mat3x2:	return 4 * 3 * 2;
		case ShaderDataType::Mat3x3:	return 4 * 3 * 3;
		case ShaderDataType::Mat3x4:	return 4 * 3 * 4;
		case ShaderDataType::Mat4x2:	return 4 * 4 * 2;
		case ShaderDataType::Mat4x3:	return 4 * 4 * 3;
		case ShaderDataType::Mat4x4:	return 4 * 4 * 4;

		default: WLD_CORE_ASSERT(false, "Unknown ShaderDataType!"); return 0;
		}
	}

	uint32_t BufferElement::GetComponentCount() const
	{
		switch (Type)
		{
		case ShaderDataType::None:		LOG_CORE_WARNING("shader type is none my not work"); return 0;
		case ShaderDataType::Bool:		return 1;
		case ShaderDataType::Int:		return 1;
		case ShaderDataType::Int2:		return 2;
		case ShaderDataType::Int3:		return 3;
		case ShaderDataType::Int4:		return 4;
		case ShaderDataType::Float:		return 1;
		case ShaderDataType::Float2:	return 2;
		case ShaderDataType::Float3:	return 3;
		case ShaderDataType::Float4:	return 4;
		case ShaderDataType::Mat2x2:	return 2 * 2;
		case ShaderDataType::Mat2x3:	return 2 * 3;
		case ShaderDataType::Mat2x4:	return 2 * 4;
		case ShaderDataType::Mat3x2:	return 3 * 2;
		case ShaderDataType::Mat3x3:	return 3 * 3;
		case ShaderDataType::Mat3x4:	return 3 * 4;
		case ShaderDataType::Mat4x2:	return 4 * 2;
		case ShaderDataType::Mat4x3:	return 4 * 3;
		case ShaderDataType::Mat4x4:	return 4 * 4;

		default: WLD_CORE_ASSERT(false, "Unknown ShaderDataType!"); return 0;
		}
	}

	void BufferLayout::CalculateOffsetsAndStride()
	{
		uint32_t offset = 0;
		m_Stride = 0;
		for (auto& element : m_Elements)
		{
			element.Offset = offset;
			offset += element.Size;
			m_Stride += element.Size;
		}
	}
}