#pragma once

#include <glm/glm.hpp>

#include "camera_controller.h"
#include "lc_client/eng_graphics/camera/camera.h"
#include "lc_client/eng_input/i_input.h"



class OrbitalCameraController : public CameraController {
public:
	OrbitalCameraController(Camera* pCamera, IInput* pInput);

	void update();

	glm::vec3 m_originPosition;
	float m_radius;

private:
	Camera* m_pCamera = nullptr;
	IInput* m_pInput = nullptr;
	
	glm::vec2 m_lastMousePosition;
};
