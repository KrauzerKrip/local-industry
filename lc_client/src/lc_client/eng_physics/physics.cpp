#include "physics.h"

#include "lc_client/eng_scene/entt/components.h"
#include <glm/glm.hpp>

Physics::Physics(entt::registry* pRegistry) { m_pRegistry = pRegistry; }


std::pair<entt::entity, RaycastIntersection> Physics::getMinimumDistanceIntersection(
	std::unordered_map<entt::entity, RaycastIntersection>& intersections) {

	auto firstElement = *intersections.begin();

	entt::entity minDistanceEntity = firstElement.first;
	RaycastIntersection minRaycastIntersection(firstElement.second.point, firstElement.second.distance);

	for (auto& [ent, raycastIntersection] : intersections) {
		if (raycastIntersection.distance < minRaycastIntersection.distance) {
			minDistanceEntity = ent;
			minRaycastIntersection = raycastIntersection;
		}
	}

	return std::pair<entt::entity, RaycastIntersection>(minDistanceEntity, minRaycastIntersection);
}
