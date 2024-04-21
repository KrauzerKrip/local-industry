#pragma once

#pragma once

#include "game/control/mouse_raycast_observer.h"
#include "components.h"


class TradeControlSystem : public MouseRaycastObserver {
public:
	TradeControlSystem(entt::registry* pRegistry);

	void onAction(std::string action, entt::entity entity, glm::vec3 position, float distance) override;
	void onMouseMove(entt::entity entity, glm::vec3 position, float distance) override;

private:
	entt::registry* m_pRegistry = nullptr;
};