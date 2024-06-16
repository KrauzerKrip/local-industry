#include "agriculture_system.h"

#include "components.h"
#include "game/character/components.h" 
#include "game/inventory/components.h"


AgricultureSystem::AgricultureSystem(entt::registry* pRegistry) : m_treeSystem(pRegistry) { m_pRegistry = pRegistry; }

void AgricultureSystem::update(double updateInterval) {
	auto tasks = m_pRegistry->view<Harvestable, Task, CharacterAssignedTo>(entt::exclude<Harvested>);
	for (auto&& [entity, harvestable, task, character] : tasks.each()) {
		if (task.progress == TaskProgress::COMPLETED) {
			m_pRegistry->emplace<Harvested>(entity, Harvested(character.characterEntity));
		}
	}

	auto harvestedView = m_pRegistry->view<Harvestable, Harvested>(entt::exclude<InventoryLoad>);
	for (auto&& [entity, harvestable, harvested] : harvestedView.each()) {
		m_pRegistry->emplace<InventoryLoad>(entity, InventoryLoad(harvested.by, harvestable.yield, harvestable.massOfYield));
	} 

	auto harvestedDoneView = m_pRegistry->view<Harvestable, Harvested, InventoryLoaded>();
	for (auto&& [entity, harvestable, harvested, placed] : harvestedDoneView.each()) {
		m_pRegistry->destroy(entity);
	}

	//TODO: add InventoryCantPlace handling

	m_treeSystem.update(updateInterval);
}

void AgricultureSystem::machineUpdate(double updateInterval) { m_treeSystem.machineUpdate(updateInterval); }
