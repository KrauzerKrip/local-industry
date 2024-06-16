#pragma once

#include <entt/entt.hpp>


class ConnectionSystem {
public:
	ConnectionSystem(entt::registry* pRegistry);

	void update();
	void machineUpdate();

private:
	entt::registry* m_pRegistry = nullptr;
};