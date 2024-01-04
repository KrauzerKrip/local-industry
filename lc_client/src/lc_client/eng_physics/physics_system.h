#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include "lc_client/eng_scene/entt/components.h"
#include "raycast/ray.h"
#include "lc_client/tier0/conpar/parameters.h"
#include "physics_visualizer.h"


class PhysicsSystem {
public:
	PhysicsSystem(Parameters* pParameters, entt::registry* pRegistry);

	void update();
	template <typename... Components, typename... Exclude> 
	RaycastResult raycast(RaycastQuery query, entt::exclude_t<Exclude...> exclude = {});

private:
	void updateVertices();
	void updateRaycast();
	void transformVertices(std::vector<glm::vec3>& vertices, Transform& transform);

	template <typename... Components, typename... Exclude>
	std::unordered_map<entt::entity, RaycastIntersection> getIntersections(
		RaycastQuery query, entt::exclude_t<Exclude...> exclude = {});
	std::pair<entt::entity, RaycastIntersection> getMinimumDistanceIntersection(
		std::unordered_map<entt::entity, RaycastIntersection>& intersections);

	PhysicsVisualizer m_physicsVisualizer;

	entt::registry* m_pRegistry = nullptr;
};
