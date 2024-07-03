#pragma once
#include "Engine/src/core/EngineCore.h"
#include <glm/glm.hpp>


namespace WLD::Camera
{
	class WLD_API PerspectiveCamera
	{
	public:
		PerspectiveCamera();
		PerspectiveCamera(float fov, float aspectRatio, float nearClip, float farClip);
		PerspectiveCamera(float fov, float hWindow, float wWindow, float nearClip, float farClip);

		void setProjection(float fov, float aspectRatio, float nearClip, float farClip);
		void setProjection(float fov, float hWindow, float wWindow, float nearClip, float farClip);

		void setView(const glm::mat4& view);
		void setPosition(const glm::vec3& position);
		void setRotation(const glm::vec3& rotation);

		void setPos(const glm::vec3& pos);
//		void setFront(const glm::vec3& front);
		void setFront(const glm::vec2& front);
		void setUp(const glm::vec3& up);
		
		glm::mat4 getProjection() const;

	private:
		void recalculateVP();

	private:
		glm::mat4 m_VP;
		glm::mat4 m_Projection;

		glm::vec3 m_Pos;
		glm::vec3 m_Front;
		glm::vec3 m_Up;

		glm::mat4 m_Rotation;
		glm::vec3 m_Position;
		glm::mat4 m_View;
	};
}