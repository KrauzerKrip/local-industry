#include "camera.h"

#include <iostream>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>


Camera::Camera() {

 	m_position = glm::vec3(0, 0, 1);
	//m_rotation = glm::vec3(45, 0, 45);

	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraDirection = glm::normalize(m_position - cameraTarget);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

	m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
}

Camera::~Camera() {
}

glm::mat4 Camera::getViewMatrix() {
	glm::mat4 view;

	glm::vec3 direction = m_direction;
	//direction.x = cos(glm::radians(m_rotation.z)) * cos(glm::radians(m_rotation.x));
	//direction.y = sin(glm::radians(m_rotation.x));
	//direction.z = sin(glm::radians(m_rotation.z)) * cos(glm::radians(m_rotation.x));

	m_cameraFront = glm::normalize(direction);

	m_cameraRight = -glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), m_cameraFront));

	view = glm::lookAt(m_position, m_position + m_cameraFront, glm::vec3(0.0f, 1.0f, 0.0f));
	return view;
}

//glm::mat4 Camera::getModelMatrix() {
//	glm::mat4 model(1.0f);
//	model *= glm::inverse(getViewMatrix());
//}

glm::vec3 Camera::getPosition() {

	return m_position;
}

void Camera::setPosition(glm::vec3 position) {
	m_position = position;
}

//glm::vec3 Camera::getRotation() {
//	return m_rotation;
//}
//
//void Camera::setRotation(glm::vec3 rotation) {
//	m_rotation = rotation; }


void Camera::setDirection(glm::vec3 direction) { 
	m_direction = direction;
}

glm::vec3 Camera::getCameraFront() {
	return m_cameraFront;
}

glm::vec3 Camera::getCameraRight() {
	return m_cameraRight;
}
