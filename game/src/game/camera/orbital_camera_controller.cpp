#include "orbital_camera_controller.h"

#include <iostream>


OrbitalCameraController::OrbitalCameraController(Camera* pCamera, IInput* pInput) { 
	m_pCamera = pCamera;
	m_pInput = pInput;

	m_originPosition = glm::vec3(10, 0, 0);
	m_radius = 1;

	m_lastMousePosition = glm::vec2(0);

	m_pInput->addMouseCallback([this](glm::vec2 position) {
		float angleX = 0;

		if (m_pInput->isKeyPressed(KeyCode::MOUSE_BUTTON_RIGHT)) {
			glm::vec2 mouseOffset = position - m_lastMousePosition;

			float c = 360.0f / (1080.0f * 10.0f);

			angleX = mouseOffset.x * c;
		};

		glm::vec3 camPos = m_pCamera->getPosition();

		float ang = glm::radians(angleX);

		glm::vec3 relativeCamPos = camPos - m_originPosition;

		float x = relativeCamPos.x * cos(ang) - relativeCamPos.z * sin(ang);
		float z = relativeCamPos.x * sin(ang) + relativeCamPos.z * cos(ang);

		camPos = m_originPosition + glm::vec3(x, 0, z);
		// glm::vec3 pos = m_pCamera->getPosition() + glm::vec3(xOffset, 0, zOffset);

		m_pCamera->setPosition(camPos);

		glm::vec3 lookAt = m_originPosition - m_pCamera->getPosition();
		glm::vec3 lookAtNormalized = glm::normalize(lookAt);

		m_pCamera->setDirection(lookAtNormalized);

		std::cout << camPos.x << " " << camPos.z << std::endl << std::endl;

		m_lastMousePosition = position;
	});
}

void OrbitalCameraController::update() {
}
