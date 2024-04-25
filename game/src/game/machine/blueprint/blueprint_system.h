#pragma once

#include <entt/entt.hpp>


class BlueprintSystem {
public:
	BlueprintSystem(entt::registry* pRegistry);

	void update(float updateInterval);

private:
	entt::registry* m_pRegistry = nullptr;
};