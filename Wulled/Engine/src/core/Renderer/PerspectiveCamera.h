#pragma once
#include "Engine/src/core/EngineCore.h"
#include <glm/glm.hpp>


namespace WLD
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

		glm::mat4 getProjection() const;

	private:
		glm::mat4 m_Projection;
		glm::mat4 m_View;
		glm::mat4 m_Rotation;

		glm::vec3 m_Position;
	};
}