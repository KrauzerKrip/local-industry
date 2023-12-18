#pragma once

#include <entt/entt.hpp>

#include "mouse_raycast_system.h"
#include "selection_system.h"
#include "lc_client/eng_input/i_input.h"
#include "game/control/action_control.h"
#include "lc_client/eng_graphics/i_window.h"
#include "lc_client/eng_graphics/graphics_settings.h"
#include "lc_client/eng_graphics/camera/camera.h"
#include "character_control_system.h"
#include "game/camera/camera_controller.h"


class ControlSystem {
public:
	ControlSystem(GraphicsSettings* pSettings, IInput* pInput, Camera* pCamera, ActionControl* pActionControl,
		entt::registry* pRegistry);
	~ControlSystem();

	void input();
	void update();

private:
	MouseRaycastSystem* m_pMouseRaycastSystem = nullptr;
	SelectionSystem* m_pSelectionSystem = nullptr;
	CharacterControlSystem* m_pCharacterControlSystem = nullptr;
	CameraController* m_pCameraController = nullptr;
};
