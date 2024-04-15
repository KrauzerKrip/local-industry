#pragma once

#include <glm/glm.hpp>

#include "camera_controller.h"
#include "lc_client/eng_graphics/camera/camera.h"
#include "lc_client/eng_input/i_input.h"
#include "game/control/action_control.h"


class OrbitalCameraController : public CameraController {
public:
	OrbitalCameraController(Camera* pCamera, IInput* pInput, ActionControl* pActionControl);

	void input(double deltaTime);

	glm::vec3 m_originPosition;
	float m_radius;

private:
	Camera* m_pCamera = nullptr;
	IInput* m_pInput = nullptr;
	ActionControl* m_pActionControl = nullptr;

	glm::vec3 m_sphericalCoords;

	float m_radiusChangeSpeed;
	float m_targetRadius;
	float m_minimusRadius;
	
	glm::vec2 m_lastMousePosition;

	bool m_yAxisCam;
};
