#pragma once

#include <entt/entt.hpp>

#include "lc_client/tier0/console/i_console.h"


class DepositTaskSystem {
public:
	DepositTaskSystem(entt::registry* pRegistry, IConsole* pConsole);

	void update(double updateInterval);

private:
	entt::registry* m_pRegistry = nullptr;
	IConsole* m_pConsole = nullptr;
};