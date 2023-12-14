#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include "lc_client/eng_scene/entt/components.h"
#include "raycast/ray.h"
#include "lc_client/tier0/conpar/parameters.h"
#include "physics_visualizer.h"


class PhysicsSystem {
public:
	PhysicsSystem(Parameters* pParameters, entt::registry* pSceneRegistry, entt::registry* pMapRegistry);

	void update();

private:
	void updateVertices();
	void updateRaycast();
	void transformVertices(std::vector<glm::vec3>& vertices, Transform& transform);

	std::unordered_map<entt::entity, RaycastIntersection> getIntersections(RaycastQuery query);
	std::pair<entt::entity, RaycastIntersection> getMinimumDistanceIntersection(
		std::unordered_map<entt::entity, RaycastIntersection>& intersections);

	PhysicsVisualizer m_physicsVisualizer;

	entt::registry* m_pSceneRegistry = nullptr;
	entt::registry* m_pMapRegistry = nullptr;
};
