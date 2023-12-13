#pragma once

#include <entt/entt.hpp>

#include "lc_client/tier0/conpar/parameters.h"


class PhysicsVisualizer {
public:
	PhysicsVisualizer(Parameters* pParameters, entt::registry* pSceneRegistry, entt::registry* pMapRegistry);
	void update();

private:
	Parameters* m_pParameters = nullptr;
	entt::registry* m_pSceneRegistry = nullptr;
	entt::registry* m_pMapRegistry = nullptr;
};
