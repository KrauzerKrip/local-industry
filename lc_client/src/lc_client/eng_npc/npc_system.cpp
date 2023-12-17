#include "npc_system.h"

#include <memory>

#include "components.h"
#include "lc_client/eng_scene/entt/components.h"


NpcSystem::NpcSystem(Parameters* pParameters, entt::registry* pRegistry) { 
	m_pParameters = pParameters;
	m_pRegistry = pRegistry; }

void NpcSystem::update() { 
	auto waypointNpcEntities = m_pRegistry->view<Npc, Waypoint, Transform>();

	for (auto&& [entity, npc, waypoint, transform] : waypointNpcEntities.each()) {

	}
}

void NpcSystem::setNpcGraph(NpcGraph* pNpcGraph) { 
	m_npcGraph = std::make_unique<NpcGraph>(*pNpcGraph);
	m_npcGraphVisualizer = std::make_unique<NpcGraphVisualizer>(m_npcGraph.get(), m_pParameters, m_pRegistry);
}
