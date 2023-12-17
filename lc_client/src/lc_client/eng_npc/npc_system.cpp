#include "npc_system.h"

#include "components.h"
#include "lc_client/eng_scene/entt/components.h"


NpcSystem::NpcSystem(entt::registry* pRegistry) { m_pRegistry = pRegistry; }

void NpcSystem::update() { 
	auto waypointNpcEntities = m_pRegistry->view<Npc, Waypoint, Transform>();

	for (auto&& [entity, npc, waypoint, transform] : waypointNpcEntities.each()) {

	}
}
