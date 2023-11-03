#pragma once

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Batumo {
	class Camera {
	public:
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

		virtual void RecalculateProjectionMatrix(float fov, float width, float height) = 0;
	protected:
		virtual void RecalculateViewMatrix() = 0;
	protected:
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
	};

	class OrthographicCamera : public Camera{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

	private:
		virtual void RecalculateViewMatrix() override;
	private:
		float m_Rotation = 0.0f;
	};

	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float fov, float width, float height);

		void Move(glm::vec3 position) { m_Position += (position.z * m_forward + position.x * m_right); RecalculateViewMatrix(); }

		const glm::vec3& GetRotation() const { return m_Rotation; }
		void SetRotation(glm::vec3 rotation) { m_Rotation = rotation; RecalculateViewMatrix();}
		void RotateDegrees(glm::vec3 rotation) { m_Rotation += rotation; RecalculateViewMatrix();}
		virtual void RecalculateProjectionMatrix(float fov, float width, float height) override;
	private:
		virtual void RecalculateViewMatrix() override;
	private:
		glm::vec3 m_right, m_up, m_forward, m_Rotation{ 0,0,0 };
	};
}

