#pragma once

#include <entt/entt.hpp>

#include "game/control/mouse_raycast_observer.h"
#include "game/control/action_control.h"
#include "mouse_raycast.h"


/**
 * System to control the plans to build machines for characters. Maybe refactor and make separate systems for character plans and placing machines.
 */
class MachineControlSystem : public MouseRaycastObserver {
public:
	MachineControlSystem(MouseRaycast* pMouseRaycast, ActionControl* pActionControl, entt::registry* pRegistry);

	void input();
	void update();
	void onSelect(entt::entity entity, glm::vec3 position, float distance);
	void onMouseMove(entt::entity entity, glm::vec3 position, float distance);

private:
	MouseRaycast* m_pMouseRaycast = nullptr;
	ActionControl* m_pActionControl = nullptr;

	entt::registry* m_pRegistry = nullptr;
};
