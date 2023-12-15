#include "selection_system.h"

#include <iostream>

#include "components.h"



SelectionSystem::SelectionSystem(entt::registry* pSceneRegistry, entt::registry* pMapRegistry) {
	m_pSceneRegistry = pSceneRegistry;
	m_pMapRegistry = pMapRegistry;
}

void SelectionSystem::onSelect(entt::entity entity, glm::vec3 position, float distance) {
	if (m_pSceneRegistry->all_of<Selectable>(entity)) {
		if (m_pSceneRegistry->all_of<Selected>(entity)) {
			unselectEntity(entity);
		}
		else {
			selectEntity(entity);
		}
	}
}

void SelectionSystem::onMouseMove(entt::entity entity, glm::vec3 position, float distance) {}

void SelectionSystem::selectEntity(entt::entity entity) {
	m_pSceneRegistry->emplace<Selected>(entity);

	auto selectedEntities = m_pSceneRegistry->view<Selectable, Selected>();
	for (auto&& [ent] : selectedEntities.each()) {
		if (ent != entity) {
			unselectEntity(ent);
		}
	}

	std::cout << "object selected" << std::endl;
}

void SelectionSystem::unselectEntity(entt::entity entity) {
	m_pSceneRegistry->remove<Selected>(entity);
	std::cout << "object unselected" << std::endl;
}
