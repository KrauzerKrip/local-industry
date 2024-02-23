#pragma once

#include <entt/entt.hpp>

#include "physics_loader.h"


class PhysicsLoadingSystem {
public:
	PhysicsLoadingSystem(PhysicsLoader* pPhysicsLoader, entt::registry* pRegistry, IConsole* pConsole);

	void update();

private:
	entt::registry* m_pRegistry = nullptr;
	PhysicsLoader* m_pPhysicsLoader = nullptr;
	IConsole* m_pConsole = nullptr;
};