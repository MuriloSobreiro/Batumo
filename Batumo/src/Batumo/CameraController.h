#pragma once

#include "Batumo/Renderer/Camera.h"
#include "Batumo/Core/DeltaTime.h"

#include "Batumo/Events/ApplicationEvent.h"
#include "Batumo/Events/MouseEvent.h"

namespace Batumo {
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(DeltaTime ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};

	class PerspectiveCameraController
	{
	public:
		PerspectiveCameraController(float aspectRatio, float fov);

		void OnUpdate(DeltaTime ts);
		void OnEvent(Event& e);

		PerspectiveCamera& GetCamera() { return m_Camera; }
		const PerspectiveCamera& GetCamera() const { return m_Camera; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_FieldOfView;
		PerspectiveCamera m_Camera;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_CameraRotation = { 0.0f, 0.0f, 0.0f };
		float m_CameraTranslationSpeed = 10.0f, m_CameraRotationSpeed = 10.0f;

		bool m_Mouse = false;
	};
}

