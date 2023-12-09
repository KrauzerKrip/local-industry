#include "orbital_camera_controller.h"

#include <iostream>


OrbitalCameraController::OrbitalCameraController(Camera* pCamera, IInput* pInput) { 
	m_pCamera = pCamera;
	m_pInput = pInput;

	m_originPosition = glm::vec3(10, 0, 0);
	m_radius = 25;

	m_lastMousePosition = glm::vec2(0);
	m_sphericalCoords = glm::vec3(0);
	m_sphericalCoords.r = m_radius;
	//m_sphericalCoords.t - theta (zenith)
	//m_sphericalCoords.p - fita (azimuth)
	// 
			//union { T x, r, s; };
			//union { T y, g, t; };
			//union { T z, b, p; };

	m_pInput->addMouseCallback([this](glm::vec2 mousePosition) {
		if (m_pInput->isKeyPressed(KeyCode::MOUSE_BUTTON_RIGHT)) {
			glm::vec2 mouseOffset = mousePosition - m_lastMousePosition;

			float c = (360.0f / (1080.0f));
			float angleX = mouseOffset.x * c;
			float angleY = mouseOffset.y * c;
			m_sphericalCoords.p += angleX * c;
			m_sphericalCoords.t -= angleY * c; 
		}

		m_lastMousePosition = mousePosition;
	});
}

void OrbitalCameraController::update() {
	m_sphericalCoords.r = m_radius;

	float r = m_sphericalCoords.r;
	float fita = glm::radians(m_sphericalCoords.p);
	float theta = glm::radians(m_sphericalCoords.t);

	//if (sin(abs(theta)) < sin(glm::radians(20.0f))) {
	//	int sign = 0;

	//	if (theta != 0) {
	//		sign = (theta / abs(theta));
	//		theta = glm::radians(25.0f * sign);
	//	}
	//	else {
	//		theta = glm::radians(25.0f);
	//	}

	//	float a = sin(abs(theta));
	//	float b = sin(glm::radians(20.0f));

	//	m_sphericalCoords.t = theta;
	//}

	//std::cout << theta << std::endl;
	//std::cout << glm::degrees(theta) << std::endl;

	float x = r * sin(theta) * cos(fita);
	float y = r * cos(theta);
	float z = r * sin(theta) * sin(fita);

	glm::vec3 cameraPosition = glm::vec3(x, y, z);
	cameraPosition += m_originPosition;

	m_pCamera->setPosition(cameraPosition);

	m_pCamera->setDirection(m_originPosition - m_pCamera->getPosition());

	if (m_radius < 5) {
		m_radius = 5;
	}
}
