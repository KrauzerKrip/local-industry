#pragma once

#include <entt/entt.hpp>


class TreeSystem {
public:
	TreeSystem(entt::registry* pRegistry);

	void update(double updateInterval);
	void machineUpdate(double updateInterval);

private:
	entt::registry* m_pRegistry = nullptr;
};