#include "blueprint_system.h"

#include "game/control/components.h"
#include "lc_client/eng_physics/entt/components.h"
#include "lc_client/eng_graphics/entt/components.h"
#include "game/item/components.h"
#include "game/character/components.h"
#include "game/inventory/components.h"


BlueprintSystem::BlueprintSystem(entt::registry* pRegistry) { 
	m_pRegistry = pRegistry;
}

void BlueprintSystem::update(float updateInterval) { 
	this->processRequests();
	this->acquireBlueprintsInInventories();
}

void BlueprintSystem::processRequests() {
	auto requests = m_pRegistry->view<BlueprintRequest>();
	for (auto&& [entity, request] : requests.each()) {
		if (this->isBlueprintAcquired(request.type)) {
			m_pRegistry->emplace<Blueprint>(entity);
			m_pRegistry->emplace<MachineRequest>(entity, request.type, request.typeString);
			m_pRegistry->emplace<Selected>(entity);
			m_pRegistry->emplace<Outline>(entity, Outline(glm::vec3(255 / 255., 255 / 255., 255 / 255.), 0.025));
			m_pRegistry->emplace<ShaderRequest>(entity, ShaderRequest("game", "base", "blueprint"));
			m_pRegistry->emplace<Transparent>(entity);
			m_pRegistry->emplace<ShaderUniforms>(entity);
			m_pRegistry->emplace<MachineSelectable>(entity);
		}
		m_pRegistry->remove<BlueprintRequest>(entity);
	}
}

void BlueprintSystem::acquireBlueprintsInInventories() {
	auto characters = m_pRegistry->view<GameCharacter, Inventory>();

	for (auto&& [entity, character, inventory] : characters.each()) {
		for (auto [item, mass] : inventory.items) {
			if (m_pRegistry->all_of<BlueprintItem>(item) && !m_pRegistry->all_of<BlueprintAcquired>(item)) {
				m_pRegistry->emplace<BlueprintAcquired>(item);
			}
		}
	}
}

bool BlueprintSystem::isBlueprintAcquired(MachineType type) { 
	auto acquiredBlueprints = m_pRegistry->view<BlueprintItem, BlueprintAcquired>();

	for (auto&& [entity, blueprintItem] : acquiredBlueprints.each()) {
		if (blueprintItem.type == type) {
			return true;
		}
	}

	return false;
}
