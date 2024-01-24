#include "npc_system.h"

#include <memory>

#include "components.h"
#include "lc_client/eng_scene/entt/components.h"
#include <iostream>


NpcSystem::NpcSystem(Parameters* pParameters, World* pWorld) { 
	m_pParameters = pParameters;
	m_pWorld = pWorld;
	m_pRegistry = &pWorld->getRegistry();
	m_pNpcGraph = pWorld->getNpcGraph();

	m_pRegistry->on_update<Waypoint>().connect<&NpcSystem::createPath>(this);
}

void NpcSystem::update() {
	if (m_pWorld->getNpcGraph() != m_pNpcGraph) {
		m_pNpcGraph = m_pWorld->getNpcGraph();
		m_npcGraphVisualizer = std::make_unique<NpcGraphVisualizer>(m_pNpcGraph, m_pParameters, m_pRegistry);
	}

	auto pathNpcEntities = m_pRegistry->view<Npc, NpcPath, Transform, Waypoint>();
	for (auto&& [entity, npc, path, transform, waypoint] : pathNpcEntities.each()) {
		float speed = npc.speed * (1.0f / 60.0f);

		npc::GraphPath graphPath = path.graphPath;

		if (graphPath.vertices.size() == path.pointer) {
			if (glm::distance(path.endPoint, transform.position) > 0.01f) {
				glm::vec3 direction = glm::normalize(path.endPoint - transform.position);
				transform.position = transform.position + speed * direction;
			} else {
				m_pRegistry->remove<NpcPath>(entity);
			}
		}
		else {
			npc::GraphNode node = m_pNpcGraph->getNode(graphPath.vertices.at(path.pointer));

			if (glm::distance(node.position, transform.position) > 0.1f) {
				glm::vec3 direction = glm::normalize(node.position - transform.position);
				transform.position = transform.position + speed * direction;
			}
			else {
				path.pointer++;
			}
		}
	}
}

void NpcSystem::createPath(entt::registry& registry, entt::entity entity) {
	if (registry.all_of<Transform>(entity)) {
		Transform& transform = registry.get<Transform>(entity);
		Waypoint& waypoint = registry.get<Waypoint>(entity);
		unsigned int source = m_pNpcGraph->getClosestVertice(transform.position);
		unsigned int destination = m_pNpcGraph->getClosestVertice(waypoint.position);
		npc::GraphPath path = m_pNpcGraph->getShortestPath(source, destination);
		registry.emplace_or_replace<NpcPath>(entity, path, waypoint.position);
	}
}

