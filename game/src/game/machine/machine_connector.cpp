#include "machine_connector.h"

#include "components.h"


MachineConnector::MachineConnector(entt::registry* pRegistry) { m_pRegistry = pRegistry; }

bool MachineConnector::isConnectable(entt::entity blueprint, entt::entity entityConnectTo) {
    if (m_pRegistry->all_of<HeatIn>(blueprint) && m_pRegistry->all_of<HeatOut>(entityConnectTo)) {
		if (m_pRegistry->get<HeatOut>(entityConnectTo).entity) {
			return false;
		} else {
			return true;
		}
    } else {
		return false;
    }
}
