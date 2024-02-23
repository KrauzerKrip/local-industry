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
	m_pRegistry->emplace<Selected>(entity);
	m_pRegistry->emplace<Outline>(entity, Outline(glm::vec3(255 / 255., 255 / 255., 255 / 255.), 0.025));
	m_pRegistry->emplace<ShaderRequest>(entity, ShaderRequest("game", "base", "blueprint"));
	m_pRegistry->emplace<Transparent>(entity);
	m_pRegistry->emplace<ShaderUniforms>(entity);
	m_pRegistry->emplace<BlueprintInit>(entity);
	m_pRegistry->emplace<MachineSelectable>(entity);
}
