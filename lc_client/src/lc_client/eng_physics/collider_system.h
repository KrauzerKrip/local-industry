#pragma once

#include <entt/entt.hpp>


class ColliderSystem {
public:
	ColliderSystem(entt::registry* pRegistry);

	void update();

private:
	entt::registry* m_pRegistry = nullptr;
};