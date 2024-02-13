#include "machine_connector.h"

#include "components.h"


MachineConnector::MachineConnector(entt::registry* pRegistry) { m_pRegistry = pRegistry; }

void MachineConnector::connect(ConnectionType type, entt::entity entity, entt::entity entityConnectTo) {
	if (type == ConnectionType::HEAT) {
		if (checkHeat(entity, entityConnectTo)) {
			m_pRegistry->get<HeatOut>(entityConnectTo).entity = entity;
		} 
	} else if (type == ConnectionType::NONE) {

	}
}

ConnectionType MachineConnector::chooseConnectionType(entt::entity blueprint, entt::entity entityConnectTo) {
	if (checkHeat(blueprint, entityConnectTo)) {
		return ConnectionType::HEAT;
	} else {
		return ConnectionType::NONE;
	}
}

bool MachineConnector::checkHeat(entt::entity blueprint, entt::entity entityConnectTo) {
	if (m_pRegistry->all_of<HeatIn>(blueprint) && m_pRegistry->all_of<HeatOut>(entityConnectTo)) {
		if (m_pRegistry->get<HeatOut>(entityConnectTo).entity) {
			return false;
		}
	    return true;
	}
    return false;
}
