#include "odvmpch.h"
#include "CameraControllers.h"

#include "ODVM/Core/Input.h"
#include "ODVM/Core/KeyCodes.h"

namespace ODVM
{

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation, float cameraMoveSpeed, float cameraRotationSpeed)
		: m_Rotation(rotation), m_AspectRatio(aspectRatio), m_CameraSpeed(cameraMoveSpeed), m_CameraRotationSpeed(cameraRotationSpeed), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
	{
	
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		if (ODVM::Input::IsKeyPressed(ODVM_KEY_W))
			m_CameraPosition.y += m_CameraSpeed * ts * (m_ZoomLevel * 0.5f);
		
		if (ODVM::Input::IsKeyPressed(ODVM_KEY_S))
			m_CameraPosition.y -= m_CameraSpeed * ts * (m_ZoomLevel * 0.5f);
		
		if (ODVM::Input::IsKeyPressed(ODVM_KEY_A))
			m_CameraPosition.x -= m_CameraSpeed * ts * (m_ZoomLevel * 0.5f);

		if (ODVM::Input::IsKeyPressed(ODVM_KEY_D))
			m_CameraPosition.x += m_CameraSpeed * ts * (m_ZoomLevel * 0.5f);
		if (m_Rotation) {
			if (ODVM::Input::IsKeyPressed(ODVM_KEY_Q))
				m_CameraRotation.z += m_CameraRotationSpeed * ts;

			if (ODVM::Input::IsKeyPressed(ODVM_KEY_E))
				m_CameraRotation.z -= m_CameraRotationSpeed * ts;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OrthographicCameraController::OnWindowResize));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.1f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.01f);
		m_ZoomLevel = std::min(m_ZoomLevel, 20.0f);

		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

}
