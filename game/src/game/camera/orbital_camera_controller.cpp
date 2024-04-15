#include "orbital_camera_controller.h"

#include <iostream>
#include "ldk_client/local_engine/time.h"


OrbitalCameraController::OrbitalCameraController(Camera* pCamera, IInput* pInput, ActionControl* pActionControl) { 
	m_pCamera = pCamera;
	m_pInput = pInput;
	m_pActionControl = pActionControl;

	m_originPosition = glm::vec3(10, 0, 0);
	m_radius = 25;

	m_lastMousePosition = glm::vec2(0);
	m_sphericalCoords = glm::vec3(0);
	m_sphericalCoords.r = m_radius;

	m_radiusChangeSpeed = 20;
	m_targetRadius = m_radius;
	m_minimusRadius = 15;

	m_yAxisCam = false;
	//m_sphericalCoords.t - theta (zenith)
	//m_sphericalCoords.p - fita (azimuth)
	// 
			//union { T x, r, s; };
			//union { T y, g, t; };
			//union { T z, b, p; };

	m_pInput->addMouseCallback([this](glm::vec2 mousePosition) {
		if (m_pActionControl->isAction("kb_rotate_camera")) {
			glm::vec2 mouseOffset = mousePosition - m_lastMousePosition;

			float c = (360.0f / (1080.0f));
			float angleX = mouseOffset.x * c;
			float angleY = mouseOffset.y * c;
			m_sphericalCoords.p += angleX * c;
			m_sphericalCoords.t -= angleY * c; 
		}

		m_lastMousePosition = mousePosition;
	});

	
	m_pInput->addMouseWheelCallback([this](glm::vec2 offset) {
		float wheelOffset = offset.y;
		float c = 0.1 * m_radiusChangeSpeed;
		m_targetRadius = m_radius - wheelOffset * c;
	});
}

void OrbitalCameraController::input(double deltaTime) {
	m_sphericalCoords.r = m_radius;

	m_radiusChangeSpeed = m_radius * 1.5;

	float deltaRadius = m_targetRadius - m_radius;

	float timeToReach = abs(deltaRadius) / m_radiusChangeSpeed;

	float lerpTime = deltaTime / timeToReach;

	float lerp = 0;

	if (abs(m_radius - m_targetRadius) > 0.1) {
		lerp = std::lerp(0, abs(deltaRadius), lerpTime);
	}

	float radiusChangeSpeedFactor = 1;

	if (abs(deltaRadius) < lerp) {
		radiusChangeSpeedFactor = abs(deltaRadius) / lerp;
	}

	if (abs(m_radius - m_targetRadius) > 1) {
		if (m_targetRadius > m_radius) {
			m_radius += lerp * radiusChangeSpeedFactor;
		}
		else {
			m_radius -= lerp * radiusChangeSpeedFactor;
		}
	}
	
	//std::cout << radiusChangeSpeedFactor << std::endl;
	//std::cout << lerp << std::endl;
	//std::cout << m_radius << std::endl;
	//std::cout << m_targetRadius << std::endl << std::endl;
	
	float cameraSpeed = m_radius * deltaTime;

	glm::vec3 front = m_pCamera->getCameraFront();
	glm::vec3 right = m_pCamera->getCameraRight();

	if (m_pActionControl->isAction("kb_forward")) {
		m_originPosition += cameraSpeed * glm::vec3(front.x, 0, front.z);
	}
	if (m_pActionControl->isAction("kb_back")) {
		m_originPosition += cameraSpeed * -glm::vec3(front.x, 0, front.z);
	}
	if (m_pActionControl->isAction("kb_left")) {
		m_originPosition += cameraSpeed * -glm::vec3(right.x, 0, right.z);
	}
	if (m_pActionControl->isAction("kb_right")) {
		m_originPosition += cameraSpeed * glm::vec3(right.x, 0, right.z);
	}
	if (m_pActionControl->isAction("kb_up") && m_yAxisCam) {
		m_originPosition += cameraSpeed * glm::vec3(0, 1, 0);
	}
	if (m_pActionControl->isAction("kb_down") && m_yAxisCam) {
		m_originPosition += cameraSpeed * glm::vec3(0, -1, 0);
	}

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

	if (m_radius < m_minimusRadius) {
		m_radius = m_minimusRadius;
		m_radiusChangeSpeed = m_minimusRadius;
	}
}
