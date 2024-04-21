#include "trade_control_system.h"

#include "game/economy/components.h"


TradeControlSystem::TradeControlSystem(entt::registry* pRegistry) {
	m_pRegistry = pRegistry;
}

void TradeControlSystem::onAction(std::string action, entt::entity entity, glm::vec3 position, float distance) {
	if (action == "kb_select") {
		if (m_pRegistry->all_of<Trader>(entity)) {
			if (m_pRegistry->all_of<Selected>(entity)) {
				m_pRegistry->remove<Selected>(entity);
			}
			else {
				m_pRegistry->emplace<Selected>(entity);
			}
		}
	}
}

void TradeControlSystem::onMouseMove(entt::entity entity, glm::vec3 position, float distance) {}
