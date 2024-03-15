#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include "lc_client/eng_scene/entt/components.h"
#include "raycast/ray.h"
#include "lc_client/tier0/conpar/parameters.h"
#include "physics_visualizer.h"
#include "physics.h"
#include "physics_loading_system.h"
#include "physics_loader.h"
#include "collider_system.h"


class PhysicsSystem {
public:
	PhysicsSystem(Physics* pPhysics, PhysicsLoader* pPhysicsLoader, Parameters* pParameters, entt::registry* pRegistry, IConsole* pConsole);

	void update();

private:
	void updateVertices();
	void updateRaycast();
	void transformVertices(std::vector<glm::vec3>& vertices, Transform& transform);

	PhysicsVisualizer m_physicsVisualizer;
	PhysicsLoadingSystem m_physicsLoadingSystem;
	ColliderSystem m_colliderSystem;

	Physics* m_pPhysics = nullptr;
	entt::registry* m_pRegistry = nullptr;
};
