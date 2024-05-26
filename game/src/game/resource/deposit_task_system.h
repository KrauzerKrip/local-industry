#pragma once

#include <entt/entt.hpp>


class DepositTaskSystem {
public:
	DepositTaskSystem(entt::registry* pRegistry);

	void update(double updateInterval);

private:
	entt::registry* m_pRegistry = nullptr;
};