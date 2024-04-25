#include "machine_blueprint_creator.h"

#include "game/machine/components.h"
#include "game/control/components.h"
#include "lc_client/eng_physics/entt/components.h"
#include "lc_client/eng_graphics/entt/components.h"


MachineBlueprintCreator::MachineBlueprintCreator(entt::registry* pRegistry) { 
	m_pRegistry = pRegistry;
}

void MachineBlueprintCreator::createMachineBlueprint(MachineType type, std::string typeString) {
	entt::entity entity = m_pRegistry->create();
	m_pRegistry->emplace<BlueprintRequest>(entity, type, typeString);
}
