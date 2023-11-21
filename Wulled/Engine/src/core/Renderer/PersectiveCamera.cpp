#include "wldpch.h"
#include "PerspectiveCamera.h"

#include "glm/glm.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "application.h"
#include "GLFW/glfw3.h"


namespace WLD::Graphics::Camera
{
	PerspectiveCamera::PerspectiveCamera()
		: m_Projection(glm::mat4(1.0f)), m_View(glm::mat4(1.0f)), m_Rotation(glm::mat4(1.0f)), m_Position(glm::vec3(0.0f)), m_Front(glm::vec3(0.0f)), m_Up(glm::vec3(0.0f)), m_Pos(glm::vec3(0.0f))
	{
		recalculateVP();
	}

	PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float nearClip, float farClip)
		: m_Projection(glm::mat4(1.0f)), m_View(glm::mat4(1.0f)), m_Rotation(glm::mat4(1.0f)), m_Position(glm::vec3(0.0f)), m_Front(glm::vec3(0.0f)), m_Up(glm::vec3(0.0f)), m_Pos(glm::vec3(0.0f))
	{
		setProjection(fov, aspectRatio, nearClip, farClip);
	}

	PerspectiveCamera::PerspectiveCamera(float fov, float hWindow, float wWindow, float nearClip, float farClip)
		: m_Projection(glm::mat4(1.0f)), m_View(glm::mat4(1.0f)), m_Rotation(glm::mat4(1.0f)), m_Position(glm::vec3(0.0f)), m_Front(glm::vec3(0.0f)), m_Up(glm::vec3(0.0f)), m_Pos(glm::vec3(0.0f))
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
		recalculateVP();
	}

	void PerspectiveCamera::setView(const glm::mat4& view)
	{
		m_View = view;
		recalculateVP();
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

	void PerspectiveCamera::setPos(const glm::vec3& pos)
	{
		m_Pos += pos.x * m_Front;
		m_Pos += pos.y * m_Up;
		m_Pos += glm::normalize(glm::cross(m_Front, m_Up)) * pos.z;
		recalculateVP();
	}

	void PerspectiveCamera::setFront(const glm::vec3& front)
	{
		glm::vec3 direction(1.0f);
		direction.x = -(cos(glm::radians(front.x) / 2.0f) * cos(glm::radians(front.y) / 2.0f));
		direction.y = sin(glm::radians(front.y) / 2.0f);
		direction.z = -sin(glm::radians(front.x) / 2.0f) * cos(glm::radians(front.y) / 2.0f);
		m_Front = glm::normalize(direction);
		recalculateVP();
	}

	void PerspectiveCamera::setUp(const glm::vec3& up)
	{
		m_Up = up;
		recalculateVP();
	}

	glm::mat4 PerspectiveCamera::getProjection() const
	{
		return m_VP * glm::inverse(glm::translate(m_Rotation, m_Position));
	}

	void PerspectiveCamera::recalculateVP()
	{
		m_VP = m_Projection * glm::lookAt(m_Pos, m_Pos + m_Front, m_Up);
	}
}