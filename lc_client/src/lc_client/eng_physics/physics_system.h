#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include "lc_client/eng_scene/entt/components.h"
#include "raycast/ray.h"
#include "lc_client/tier0/conpar/parameters.h"
#include "physics_visualizer.h"
#include "physics.h"


class PhysicsSystem {
public:
	PhysicsSystem(Physics* pPhysics, Parameters* pParameters, entt::registry* pRegistry);

	void update();

private:
	void updateVertices();
	void updateRaycast();
	void transformVertices(std::vector<glm::vec3>& vertices, Transform& transform);

	PhysicsVisualizer m_physicsVisualizer;

	Physics* m_pPhysics = nullptr;
	entt::registry* m_pRegistry = nullptr;
};
