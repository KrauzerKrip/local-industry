#include "npc_system.h"

#include <memory>

#include "components.h"
#include "lc_client/eng_scene/entt/components.h"


NpcSystem::NpcSystem(Parameters* pParameters, World* pWorld) { 
	m_pParameters = pParameters;
	m_pWorld = pWorld;
	m_pRegistry = &pWorld->getRegistry();
	m_pNpcGraph = pWorld->getNpcGraph();
}

void NpcSystem::update() {
	if (m_pWorld->getNpcGraph() != m_pNpcGraph) {
		m_pNpcGraph = m_pWorld->getNpcGraph();
		m_npcGraphVisualizer = std::make_unique<NpcGraphVisualizer>(m_pNpcGraph, m_pParameters, m_pRegistry);		
	}

	auto waypointNpcEntities = m_pRegistry->view<Npc, Waypoint, Transform>();

	for (auto&& [entity, npc, waypoint, transform] : waypointNpcEntities.each()) {

	}
}

