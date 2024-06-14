#include "machine_connector.h"

#include "components.h"


MachineConnector::MachineConnector(entt::registry* pRegistry) { m_pRegistry = pRegistry; }

void MachineConnector::connect(
	ConnectionResourceType resourceType, ConnectionType type, entt::entity entity, entt::entity entityConnectTo) {
	Connections& entityConnections = m_pRegistry->get<Connections>(entity);
	Connections& entityConnectToConnections = m_pRegistry->get<Connections>(entityConnectTo);

	if (type == ConnectionType::IN) {
		entityConnections.inputs.at(resourceType).entity = entityConnectTo;
		entityConnectToConnections.outputs.at(resourceType).entity = entity;
	}
	else if (type == ConnectionType::OUT) {
		entityConnections.outputs.at(resourceType).entity = entityConnectTo;
		entityConnectToConnections.inputs.at(resourceType).entity = entity;
	}
}

std::tuple<ConnectionResourceType, ConnectionType> MachineConnector::chooseConnection(
	entt::entity entity, entt::entity entityConnectTo) {
	Connections& entityConnections = m_pRegistry->get<Connections>(entity);
	Connections& entityConnectToConnections = m_pRegistry->get<Connections>(entityConnectTo);

	for (auto& [resourceType, connection] : entityConnections.inputs) {
		for (auto& [resourceType_, connection_] : entityConnectToConnections.outputs) {
			if (resourceType == resourceType_) {
				return std::make_tuple(resourceType, ConnectionType::IN);
			}
		}
	}

	for (auto& [resourceType, connection] : entityConnections.outputs) {
		for (auto& [resourceType_, connection_] : entityConnectToConnections.inputs) {
			if (resourceType == resourceType_) {
				return std::make_tuple(resourceType, ConnectionType::OUT);
			}
		}
	}

	return std::make_tuple(ConnectionResourceType::NONE, ConnectionType::NONE);
}
