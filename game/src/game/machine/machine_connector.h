#pragma once

#include <tuple>

#include <entt/entt.hpp>

#include "machine_type.h"


class MachineConnector {
public:
	MachineConnector(entt::registry* pRegistry);

	void connect(ConnectionResourceType resourceType, ConnectionType type, entt::entity entity, entt::entity entityConnectTo);
	void disconnectEveryConnection(entt::entity entity);
	[[nodiscard]] std::tuple<ConnectionResourceType, ConnectionType> chooseConnection(entt::entity blueprint, entt::entity entityConnectTo);

private:

	entt::registry* m_pRegistry = nullptr;
};
