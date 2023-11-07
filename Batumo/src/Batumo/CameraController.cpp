#include "btpch.h"
#include "CameraController.h"

#include "Batumo/Input.h"
#include "Batumo/Events/KeyCodes.h"

namespace Batumo {
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{
	}
	void OrthographicCameraController::OnUpdate(DeltaTime dt)
	{
		if (Input::IsKeyPressed(BT_KEY_A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * dt;
		else if (Input::IsKeyPressed(BT_KEY_D))
			m_CameraPosition.x += m_CameraTranslationSpeed * dt;

		if (Input::IsKeyPressed(BT_KEY_W))
			m_CameraPosition.y += m_CameraTranslationSpeed * dt;
		else if (Input::IsKeyPressed(BT_KEY_S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * dt;

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(BT_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * dt;
			if (Input::IsKeyPressed(BT_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * dt;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}
	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BT_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BT_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}
	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
	PerspectiveCameraController::PerspectiveCameraController(float aspectRatio, float fov)
		: m_AspectRatio(aspectRatio), m_FieldOfView(fov), m_Camera(m_FieldOfView, m_AspectRatio)
	{
	}
	void PerspectiveCameraController::OnUpdate(DeltaTime dt)
	{
		m_CameraPosition = { 0,0,0 };
		if (Batumo::Input::IsKeyPressed(BT_KEY_A))
			m_CameraPosition.x += m_CameraTranslationSpeed * dt;
		if (Batumo::Input::IsKeyPressed(BT_KEY_D))
			m_CameraPosition.x -= m_CameraTranslationSpeed * dt;
		if (Batumo::Input::IsKeyPressed(BT_KEY_W))
			m_CameraPosition.z += m_CameraTranslationSpeed * dt;
		if (Batumo::Input::IsKeyPressed(BT_KEY_S))
			m_CameraPosition.z -= m_CameraTranslationSpeed * dt;

		if (Batumo::Input::IsKeyPressed(BT_KEY_ESCAPE)) {
			if (m_Mouse)
				Batumo::Input::DisableMouse();
			else
				Batumo::Input::EnableMouse();
			m_Mouse = !m_Mouse;
		}
		if (!m_Mouse) {
			auto rotation = Batumo::Input::GetMouseDelta();
			m_CameraRotation += glm::vec3(rotation.second * m_CameraRotationSpeed * dt, rotation.first * m_CameraRotationSpeed * dt, 0);
			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.Move(m_CameraPosition);
	}
	void PerspectiveCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BT_BIND_EVENT_FN(PerspectiveCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BT_BIND_EVENT_FN(PerspectiveCameraController::OnWindowResized));
	}
	bool PerspectiveCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_FieldOfView -= e.GetYOffset() * 0.25f;
		m_Camera.SetProjection(m_FieldOfView, m_AspectRatio);
		return false;
	}
	bool PerspectiveCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(m_FieldOfView, m_AspectRatio);
		return false;
	}
}