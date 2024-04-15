#include "agriculture_system.h"

#include "components.h"
#include "game/character/components.h" 


AgricultureSystem::AgricultureSystem(entt::registry* pRegistry) { m_pRegistry = pRegistry; }

void AgricultureSystem::update() {
	auto tasks = m_pRegistry->view<Harvestable, Task, CharacterAssignedTo>();

	for (auto&& [entity, harvestable, task, character] : tasks.each()) {
		if (task.progress == TaskProgress::COMPLETED) {
			m_pRegistry->emplace<Harvested>(entity, Harvested(character.entity));
		}
	}

	auto harvestedView = m_pRegistry->view<Harvestable, Harvested>();
	for (auto&& [entity, harvestable, harvested] : harvestedView.each()) {
		m_pRegistry->destroy(entity);
	}
}
