#include "tree_system.h"

#include "components.h"
#include <game/machine/components.h>


TreeSystem::TreeSystem(entt::registry* pRegistry) { m_pRegistry = pRegistry; }

void TreeSystem::update(double updateInterval) {}

void TreeSystem::machineUpdate(double updateInterval) { 
	auto trees = m_pRegistry->view<Tree, Connections>(); 

	for (auto&& [entity, connections] : trees.each()) {
		Connection& latexConnection = connections.outputs.at(ConnectionResourceType::LATEX);

		if (latexConnection.entity.has_value()) {
			latexConnection.resource += 0.01 * updateInterval;
		}
	}
}
