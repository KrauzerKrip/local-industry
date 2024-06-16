#include "connection_system.h"
#include "components.h"

ConnectionSystem::ConnectionSystem(entt::registry* pRegistry) { m_pRegistry = pRegistry; }

void ConnectionSystem::update() {
	auto machines = m_pRegistry->view<Connections>(entt::exclude<Blueprint>);
	for (auto&& [entity, connections] : machines.each()) {
		for (auto& [resourceType, connection] : connections.outputs) {
			if (connection.resource > 0 && connection.entity.has_value()) {
				Connection& inputConnection =
					m_pRegistry->get<Connections>(connection.entity.value()).inputs.at(resourceType);
				inputConnection.resource += connection.resource;
				connection.resource = 0;
			}
		}
	}
}

void ConnectionSystem::machineUpdate() {}
