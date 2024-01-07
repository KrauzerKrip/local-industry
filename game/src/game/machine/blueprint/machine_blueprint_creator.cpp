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
	m_pRegistry->emplace<Blueprint>(entity);
	m_pRegistry->emplace<MachineRequest>(entity, type, typeString);
	//m_pRegistry->emplace<Selected>(entity);
	//m_pRegistry->emplace<Outline>(entity, Outline(glm::vec3(1, 1, 1), 0.05));
	m_pRegistry->emplace<BoxCollider>(entity, BoxCollider(4.0f, 4.0f, 4.0f));
	m_pRegistry->emplace<ShaderRequest>(entity, ShaderRequest("game", "base", "blueprint"));
}
