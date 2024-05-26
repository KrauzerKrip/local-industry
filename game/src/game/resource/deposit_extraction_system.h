#pragma once

#include <entt/entt.hpp>


class DepositExtractionSystem {
public:
	DepositExtractionSystem(entt::registry* pRegistry);

	void update(double updateInterval);

private:
	entt::registry* m_pRegistry;
};