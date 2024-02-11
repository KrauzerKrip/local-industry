#pragma once

#include <entt/entt.hpp>


class MachineConnector {
public:
	MachineConnector(entt::registry* pRegistry);

	[[nodiscard]] bool isConnectable(entt::entity blueprint, entt::entity entityConnectTo);

private:
	entt::registry* m_pRegistry = nullptr;
};