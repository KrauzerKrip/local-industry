#pragma once

#include "game/control/mouse_raycast_observer.h"
#include "components.h"


class AgricultureControlSystem : public MouseRaycastObserver {
public:
	AgricultureControlSystem(entt::registry* pRegistry);

	void onAction(std::string action, entt::entity entity, glm::vec3 position, float distance) override;
	void onMouseMove(entt::entity entity, glm::vec3 position, float distance) override;

private:
	void addTask(entt::entity entity);
	void removeTask(entt::entity entity);

	entt::registry* m_pRegistry = nullptr;
};