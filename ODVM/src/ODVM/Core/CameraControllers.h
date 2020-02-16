#pragma once

#include "Core.h"

#include "ODVM/Core/Timesteps.h"
#include "ODVM/Renderer/Cameras.h"

#include "ODVM/Events/ApplicationEvent.h"
#include "ODVM/Events/KeyEvent.h"
#include "ODVM/Events/MouseEvent.h"
#include "ODVM/Events/Event.h"

namespace ODVM
{
	class CameraController
	{

	};

	class OrthographicCameraController : public CameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false, float cameraMoveSpeed = 2.0f, float cameraRotationSpeed = 180.0f);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		const OrthographicCamera& GetCamera() const { return m_Camera; }
		OrthographicCamera& GetCamera() { return m_Camera; }

		const glm::vec3& GetPosition() const { return m_CameraPosition; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_CameraRotation = { 0.0f, 0.0f, 0.0f };

		float m_CameraSpeed = 2.0f;
		float m_CameraRotationSpeed = 180.0f;
	};
}