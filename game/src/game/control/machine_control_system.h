#pragma once

#include <entt/entt.hpp>

#include "components.h"
#include "game/control/mouse_raycast_observer.h"
#include "game/control/action_control.h"
#include "mouse_raycast.h"
#include "game/machine/components.h"
#include "lc_client/eng_graphics/entt/components.h"


/**
 * System to control the plans to build machines for characters. Maybe refactor and make separate systems for character plans and placing machines.
 */
class MachineControlSystem : public MouseRaycastObserver {
public:
	MachineControlSystem(MouseRaycast* pMouseRaycast, ActionControl* pActionControl, entt::registry* pRegistry);

	void input();
	void update();
	void onAction(std::string action, entt::entity entity, glm::vec3 position, float distance) override;
	void onMouseMove(entt::entity entity, glm::vec3 position, float distance) override;
	[[nodiscard]] bool isConnectable(entt::entity blueprint, entt::entity entityConnectTo);

private:
	void addSelectionCallback();
	void addRotationCallback();
	void addRemoveCallback();
	void addTask(entt::entity entity);
	void removeTask(entt::entity entity);
    /**
     * \brief checks if addition's base isn't built or added to tasks.
     * \param entity 
     * \return 
     */
    bool checkIsOrphanAddition(entt::entity entity);
	void selectOrUnselect(entt::entity entity);  

	MouseRaycast* m_pMouseRaycast = nullptr;
	ActionControl* m_pActionControl = nullptr;

	entt::registry* m_pRegistry = nullptr;
	bool m_isConnection = false;
};