#include "agriculture_control_system.h"

#include "game/agriculture/components.h"
#include "game/character/components.h"

#include "lc_client/eng_graphics/entt/components.h"


AgricultureControlSystem::AgricultureControlSystem(entt::registry* pRegistry) { m_pRegistry = pRegistry; }

void AgricultureControlSystem::onAction(std::string action, entt::entity entity, glm::vec3 position, float distance) {
	if (action == "kb_build") {
		if (m_pRegistry->all_of<Harvestable>(entity)) {
			if (m_pRegistry->all_of<Task>(entity)) {
				removeTask(entity);
			}
			else {
				addTask(entity);
			}
		}
	}
}

void AgricultureControlSystem::onMouseMove(entt::entity entity, glm::vec3 position, float distance) {}

void AgricultureControlSystem::addTask(entt::entity entity) {
	auto selectedCharacter = m_pRegistry->view<GameCharacter, Selected>();
	for (auto&& [characterEntity, character] : selectedCharacter.each()) {
		m_pRegistry->emplace<CharacterAssignedTo>(entity, characterEntity);
	}
	m_pRegistry->emplace<Task>(entity);
	m_pRegistry->emplace<Outline>(entity, Outline(glm::vec3(1, 1, 1), 0.025));
}

void AgricultureControlSystem::removeTask(entt::entity entity) {
	m_pRegistry->remove<Task>(entity);
	m_pRegistry->remove<Outline>(entity);
	if (m_pRegistry->all_of<CharacterAssignedTo>(entity)) {
		m_pRegistry->remove<CharacterAssignedTo>(entity);
	}
}
