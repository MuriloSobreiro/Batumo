#include "btpch.h"
#include "Camera.h"



namespace Batumo {
	PerspectiveCamera::PerspectiveCamera(float fov, float width, float height)
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(fov), width / height, 0.1f, 100.0f);
		m_ViewMatrix = glm::mat4(1.0f);
		RecalculateViewMatrix();
	}
	void PerspectiveCamera::RecalculateViewMatrix()
	{
		float pitch = glm::radians(m_Rotation.y), yaw = glm::radians(m_Rotation.z), roll = glm::radians(m_Rotation.x);
		m_forward.x = glm::sin(roll) * glm::sin(yaw) + glm::cos(roll) * glm::cos(yaw) * glm::sin(pitch);
		m_forward.y = glm::cos(roll) * glm::sin(pitch) * glm::sin(yaw) - glm::cos(yaw) * glm::sin(roll);
		m_forward.z = glm::cos(pitch) * glm::cos(roll);
		m_forward = glm::normalize(m_forward);

		m_right.x = glm::cos(pitch) * glm::cos(yaw);
		m_right.y = glm::cos(pitch) * glm::sin(yaw);
		m_right.z = -glm::sin(pitch);
		m_right = glm::normalize(m_right);

		m_up = glm::normalize(glm::cross(m_forward, m_right));

		m_ViewMatrix = glm::lookAt(m_Position, m_Position+m_forward, m_up);
		
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewMatrix = glm::mat4(1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}