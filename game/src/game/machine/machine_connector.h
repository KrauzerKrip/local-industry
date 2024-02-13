#pragma once

#include <entt/entt.hpp>

#include "machine_type.h"


class MachineConnector {
public:
	MachineConnector(entt::registry* pRegistry);

	void connect(ConnectionType type, entt::entity entity, entt::entity entityConnectTo);
	[[nodiscard]] ConnectionType chooseConnectionType(entt::entity blueprint, entt::entity entityConnectTo);

private:
	[[nodiscard]] bool checkHeat(entt::entity blueprint, entt::entity entityConnectTo);

	entt::registry* m_pRegistry = nullptr;
};
