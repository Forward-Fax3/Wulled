#pragma once
#include "Engine/src/core/EngineCore.h"
#include <glm/glm.hpp>


namespace WLD::Camera
{
	template<typename T = float, glm::qualifier Q = glm::defaultp>
	class WLD_API _PerspectiveCamera
	{
	public:
		_PerspectiveCamera();
		_PerspectiveCamera(float fov, float hWindow, float wWindow, float nearClip, float farClip);
		_PerspectiveCamera(float fov, float aspectRatio, float nearClip, float farClip);

		void SetProjection(float fov, float hWindow, float wWindow, float nearClip, float farClip);
		void SetProjection(float fov, float aspectRatio, float nearClip, float farClip);

		void SetView(const glm::mat<4, 4, T, Q>& view);
		void SetPosition(const glm::vec<3, T, Q>& position);
		void SetRotation(const glm::vec<3, T, Q>& rotation);

		void SetPos(const glm::vec<3, T, Q>& pos);

//		void SetFront(const glm::vec3& front);
		void SetFront(const glm::vec<2, T, Q>& front);
		void SetUp(const glm::vec<3, T, Q>& up);
		
		glm::mat<4, 4, T, Q> GetProjection();

	private:
		void RecalculateVP();
		void SetupFrontAndRotation();

	private:
		glm::mat<4, 4, T, Q> m_VP, m_Projection = glm::mat<4, 4, T, Q>(static_cast<T>(1.0));

		glm::vec<3, T, Q> m_Front, m_Pos = glm::vec<3, T, Q>(static_cast<T>(0.0)), m_Up = glm::vec<3, T, Q>(static_cast<T>(0.0));

		glm::mat<4, 4, T, Q> m_Rotation;
		glm::vec<3, T, Q> m_Position = glm::vec<3, T ,Q>(static_cast<T>(0.0));
		glm::mat<4, 4, T, Q> m_View = glm::mat<4, 4, T, Q>(static_cast<T>(1.0));

		bool m_RecalculateVP = false;
	};

	using PerspectiveCamera = _PerspectiveCamera<float, glm::defaultp>;
}
