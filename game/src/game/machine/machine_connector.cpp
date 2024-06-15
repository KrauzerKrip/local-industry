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

void MachineConnector::disconnectEveryConnection(entt::entity entity) {
	Connections& connections = m_pRegistry->get<Connections>(entity);

	for (auto& [resourceType, connection] : connections.inputs) {
		if (connection.entity.has_value()) {
			Connections& connectedEntityConnections = m_pRegistry->get<Connections>(connection.entity.value());
			for (auto& [k, v] : connectedEntityConnections.outputs) {
				if (k == resourceType) {
					v.entity = std::nullopt;
				}
			}
			connection.entity = std::nullopt;
		}
	}

	for (auto& [resourceType, connection] : connections.outputs) {
		if (connection.entity.has_value()) {
			Connections& connectedEntityConnections = m_pRegistry->get<Connections>(connection.entity.value());
			for (auto& [k, v] : connectedEntityConnections.inputs) {
				if (k == resourceType) {
					v.entity = std::nullopt;
				}
			}
			connection.entity = std::nullopt;
		}
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
