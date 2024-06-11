#include "deposit_control_system.h"

#include "game/resource/components.h"
#include "game/character/components.h"
#include "lc_client/eng_graphics/entt/components.h"


DepositControlSystem::DepositControlSystem(entt::registry* pRegistry) {
	m_pRegistry = pRegistry;
}

void DepositControlSystem::onAction(std::string action, entt::entity entity, glm::vec3 position, float distance) {
	if (action == "kb_build") {
		if (m_pRegistry->all_of<ResourceDeposit>(entity)) {
			if (m_pRegistry->all_of<Task>(entity)) {
				removeTask(entity);
			}
			else {
				addTask(entity);
			}
		}
	}
}

void DepositControlSystem::onMouseMove(entt::entity entity, glm::vec3 position, float distance) {}

void DepositControlSystem::addTask(entt::entity entity) {
	ResourceDeposit& resourceDeposit = m_pRegistry->get<ResourceDeposit>(entity);
	m_pRegistry->emplace<TaskRequest>(entity, TaskRequest("Extract", resourceDeposit.massOfResource * 10));
	m_pRegistry->emplace<Outline>(entity, Outline(glm::vec3(1, 1, 1), 0.025));
}

void DepositControlSystem::removeTask(entt::entity entity) {
	m_pRegistry->emplace<RemoveTaskRequest>(entity, RemoveTaskRequest());
	m_pRegistry->remove<Outline>(entity);
}
