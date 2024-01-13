#pragma once

#include <glm/glm.hpp>

#include "lc_client/eng_physics/entt/components.h"


class MouseRaycastObserver {
public:
	virtual void onAction(std::string action, entt::entity entity, glm::vec3 position, float distance) = 0;
	virtual void onMouseMove(entt::entity entity, glm::vec3 position, float distance) = 0;
};
