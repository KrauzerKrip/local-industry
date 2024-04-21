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
#include "machine_control_system.h"
#include "lc_client/eng_physics/physics.h"
#include "mouse_raycast.h"
#include "agriculture_control_system.h"
#include "trade_control_system.h"


class ControlSystem {
public:
	ControlSystem(GraphicsSettings* pSettings, IInput* pInput, Camera* pCamera, ActionControl* pActionControl,
		Physics* pPhysics, 
		entt::registry* pRegistry);
	~ControlSystem();

	void input(double deltaTime);
	void update(double updateInterval);

private:
	MouseRaycast m_mouseRaycast;
	SelectionSystem m_selectionSystem;
	CharacterControlSystem m_characterControlSystem;
	MachineControlSystem m_machineControlSystem;
	MouseRaycastSystem m_mouseRaycastSystem;
	AgricultureControlSystem m_agricultureControlSystem;
	TradeControlSystem m_tradeControlSystem;

	CameraController* m_pCameraController = nullptr;
};
