#include "machine_blueprint_creator.h"

#include "game/machine/components.h"


MachineBlueprintCreator::MachineBlueprintCreator(entt::registry* pRegistry) { 
	m_pRegistry = pRegistry;
}

void MachineBlueprintCreator::createMachineBlueprint(MachineType type, std::string typeString) { 
	entt::entity entity = m_pRegistry->create();
	m_pRegistry->emplace<Blueprint>(entity);
	m_pRegistry->emplace<MachineRequest>(entity, type, typeString);
}
