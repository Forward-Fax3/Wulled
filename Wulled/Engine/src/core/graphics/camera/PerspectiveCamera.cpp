#include "wldpch.h"
#include "PerspectiveCamera.h"

#include "glm/glm.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "application.h"
#include "GL/glew.h"
// #include "glad/glad.h"


namespace WLD::Camera
{
	template<typename T, glm::qualifier Q>
	inline _PerspectiveCamera<T, Q>::_PerspectiveCamera()
	{
		SetupFrontAndRotation();
	}

	template<typename T, glm::qualifier Q>
	inline _PerspectiveCamera<T, Q>::_PerspectiveCamera(float fov, float hWindow, float wWindow, float nearClip, float farClip)
	{
		SetProjection(fov, wWindow / hWindow, nearClip, farClip);
		SetupFrontAndRotation();
	}

	template<typename T, glm::qualifier Q>
	inline _PerspectiveCamera<T, Q>::_PerspectiveCamera(float fov, float aspectRatio, float nearClip, float farClip)
	{
		SetProjection(fov, aspectRatio, nearClip, farClip);
		SetupFrontAndRotation();
	}

	template<typename T, glm::qualifier Q>
	inline void _PerspectiveCamera<T, Q>::SetProjection(float fov, float hWindow, float wWindow, float nearClip, float farClip)
	{
		SetProjection(fov, wWindow / hWindow, nearClip, farClip);
	}

	template<typename T, glm::qualifier Q>
	inline void _PerspectiveCamera<T, Q>::SetProjection(float fov, float aspectRatio, float nearClip, float farClip)
	{
		m_Projection = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
		m_RecalculateVP = true;
	}

	template<typename T, glm::qualifier Q>
	inline void _PerspectiveCamera<T, Q>::SetView(const glm::mat<4, 4, T, Q>& view)
	{
		m_View = view;
		m_RecalculateVP = true;
	}

	template<typename T, glm::qualifier Q>
	inline void _PerspectiveCamera<T, Q>::SetPosition(const glm::vec<3, T, Q>& position)
	{
		m_Position = position;
	}

	template<typename T, glm::qualifier Q>
	inline void _PerspectiveCamera<T, Q>::SetRotation(const glm::vec<3, T, Q>& rotation)
	{
		m_Rotation = glm::rotate(glm::mat<4, 4, T, Q>(static_cast<T>(1.0)), glm::radians(rotation.x), glm::vec<3, T, Q>(0.0f, 1.0f, 0.0f));
		m_Rotation = glm::rotate(m_Rotation, glm::radians(rotation.y), glm::vec<3, T, Q>(1.0f, 0.0f, 0.0f));
		m_Rotation = glm::rotate(m_Rotation, glm::radians(rotation.z), glm::vec<3, T, Q>(0.0f, 0.0f, 1.0f));
	}

	template<typename T, glm::qualifier Q>
	inline void _PerspectiveCamera<T, Q>::SetPos(const glm::vec<3, T, Q>& pos)
	{
		m_Pos += pos.x * m_Front;
		m_Pos += pos.y * m_Up;
		m_Pos += glm::normalize(glm::cross(m_Front, m_Up)) * pos.z;
		m_RecalculateVP = true;
	}

	template<typename T, glm::qualifier Q>
	inline void _PerspectiveCamera<T, Q>::SetFront(const glm::vec<2, T, Q>& front)
	{
		glm::vec<3, T, Q> direction(static_cast<T>(0.0));
		direction.x = -(cos(glm::radians(front.x) / 2.0f) * cos(glm::radians(front.y) / 2.0f));
		direction.y = sin(glm::radians(front.y) / 2.0f);
		direction.z = -sin(glm::radians(front.x) / 2.0f) * cos(glm::radians(front.y) / 2.0f);
		m_Front = glm::normalize(direction);
		m_RecalculateVP = true;
	}

	template<typename T, glm::qualifier Q>
	inline void _PerspectiveCamera<T, Q>::SetUp(const glm::vec<3, T, Q>& up)
	{
		m_Up = up;
		m_RecalculateVP = true;
	}

	template<typename T, glm::qualifier Q>
	inline glm::mat<4, 4, T, Q> _PerspectiveCamera<T, Q>::GetProjection()
	{
		if (m_RecalculateVP)
			RecalculateVP();

		return m_VP * glm::inverse(glm::translate(m_Rotation, m_Position));
	}

	template<typename T, glm::qualifier Q>
	inline void _PerspectiveCamera<T, Q>::RecalculateVP()
	{
		m_VP = m_Projection * glm::lookAt(m_Pos, m_Pos + m_Front, m_Up);
	}

	template<typename T, glm::qualifier Q>
	void _PerspectiveCamera<T, Q>::SetupFrontAndRotation()
	{
		SetRotation(glm::vec<3, T, Q>(static_cast<T>(0.0)));
		SetFront(glm::vec<3, T, Q>(static_cast<T>(0.0)));
	}

	GLM_DEFINE_ALL_TYPES_FLOAT(_PerspectiveCamera);
}