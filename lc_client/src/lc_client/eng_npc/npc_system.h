#pragma once

#include <entt/entt.hpp>


class NpcSystem {
public:
	NpcSystem(entt::registry* pRegistry);

	void update();

private:
	entt::registry* m_pRegistry;
};
