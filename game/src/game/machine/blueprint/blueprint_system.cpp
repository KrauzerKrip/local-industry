#include "blueprint_system.h"

#include "game/machine/components.h"
#include "game/control/components.h"
#include "lc_client/eng_physics/entt/components.h"
#include "lc_client/eng_graphics/entt/components.h"


BlueprintSystem::BlueprintSystem(entt::registry* pRegistry) { m_pRegistry = pRegistry; }

void BlueprintSystem::update(float updateInterval) { 
	auto requests = m_pRegistry->view<BlueprintRequest>();

	for (auto&& [entity, request] : requests.each()) {
		m_pRegistry->emplace<Blueprint>(entity);
		m_pRegistry->emplace<MachineRequest>(entity, request.type, request.typeString);
		m_pRegistry->emplace<Selected>(entity);
		m_pRegistry->emplace<Outline>(entity, Outline(glm::vec3(255 / 255., 255 / 255., 255 / 255.), 0.025));
		m_pRegistry->emplace<ShaderRequest>(entity, ShaderRequest("game", "base", "blueprint"));
		m_pRegistry->emplace<Transparent>(entity);
		m_pRegistry->emplace<ShaderUniforms>(entity);
		m_pRegistry->emplace<MachineSelectable>(entity);

		m_pRegistry->remove<BlueprintRequest>(entity);
	}
}
