/*
#pragma once
#include "renderer.h"

#include <vector>

#include <stdexcept>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


struct vertexBufferElement
{
	uint32_t type;
	uint32_t count;
	uint8_t normalized;

	static uint32_t getSizeOfType(uint32_t type)
	{
		switch (type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}
		ASSERT(true);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<vertexBufferElement> m_elements;
	uint32_t m_stride;

public:
	VertexBufferLayout()
		: m_stride(0) {}

	template<class T>
	void Push(uint32_t count)
	{
		std::runtime_error(false);
	}

	template<>
	void Push<float>(uint32_t count)
	{
		m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_stride += count * vertexBufferElement::getSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<uint32_t>(uint32_t count)
	{
		m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_stride += count * vertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<uint8_t>(uint32_t count)
	{
		m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_stride += count * vertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<vertexBufferElement>& getElements() const { return m_elements; }
	inline uint32_t getStride() const { return m_stride; }
};
*/