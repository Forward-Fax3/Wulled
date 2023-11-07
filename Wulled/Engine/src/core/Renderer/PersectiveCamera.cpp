#include "wldpch.h"
#include "PerspectiveCamera.h"

#include "glm/glm.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>


namespace WLD
{
	PerspectiveCamera::PerspectiveCamera()
		: m_Projection(glm::mat4(1.0f)), m_View(glm::mat4(1.0f)), m_Rotation(glm::mat4(1.0f)), m_Position(glm::vec3(0.0f))
	{

	}

	PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float nearClip, float farClip)
		: m_Projection(glm::mat4(1.0f)), m_View(glm::mat4(1.0f)), m_Rotation(glm::mat4(1.0f)), m_Position(glm::vec3(0.0f))
	{
		setProjection(fov, aspectRatio, nearClip, farClip);
	}

	PerspectiveCamera::PerspectiveCamera(float fov, float hWindow, float wWindow, float nearClip, float farClip)
		: m_Projection(glm::mat4(1.0f)), m_View(glm::mat4(1.0f)), m_Rotation(glm::mat4(1.0f)), m_Position(glm::vec3(0.0f))
	{
		setProjection(fov, wWindow / hWindow, nearClip, farClip);
	}

	void PerspectiveCamera::setProjection(float fov, float hWindow, float wWindow, float nearClip, float farClip)
	{
		setProjection(fov, wWindow / hWindow, nearClip, farClip);
	}

	void PerspectiveCamera::setProjection(float fov, float aspectRatio, float nearClip, float farClip)
	{
		m_Projection = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
	}

	void PerspectiveCamera::setView(const glm::mat4& view)
	{
		m_View = view;
	}

	void PerspectiveCamera::setPosition(const glm::vec3& position)
	{
		m_Position = position;
	}

	void PerspectiveCamera::setRotation(const glm::vec3& rotation)
	{
		m_Rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(0.0f, 1.0f, 0.0f));
		m_Rotation = glm::rotate(m_Rotation, glm::radians(rotation.y), glm::vec3(1.0f, 0.0f, 0.0f));
		m_Rotation = glm::rotate(m_Rotation, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	}

	glm::mat4 PerspectiveCamera::getProjection() const
	{
		return m_Projection * m_View * glm::inverse(glm::translate(m_Rotation, m_Position));
	}
}