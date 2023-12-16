#pragma once

#include <entt/entt.hpp>

#include "mouse_raycast_system.h"
#include "mouse_raycast_observer.h"


class SelectionSystem : public MouseRaycastObserver {
public:
	SelectionSystem(entt::registry* pRegistry);

	void onSelect(entt::entity entity, glm::vec3 position, float distance);
	void onMouseMove(entt::entity entity, glm::vec3 position, float distance);

private:
	void selectEntity(entt::entity entity);
	void unselectEntity(entt::entity entity);

	entt::registry* m_pRegistry = nullptr;
};
