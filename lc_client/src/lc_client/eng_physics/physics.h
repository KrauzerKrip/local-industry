#pragma once

#include <entt/entt.hpp>
#include "raycast/ray.h"


class Physics {
public:
	Physics(entt::registry* pRegistry);

	template <typename... Components, typename... Exclude>
	RaycastResult raycast(RaycastQuery query, entt::exclude_t<Exclude...> exclude = {});

private:
	template <typename... Components, typename... Exclude>
	std::unordered_map<entt::entity, RaycastIntersection> getIntersections(
		RaycastQuery query, entt::exclude_t<Exclude...> exclude = {});
	std::pair<entt::entity, RaycastIntersection> getMinimumDistanceIntersection(
		std::unordered_map<entt::entity, RaycastIntersection>& intersections);

	entt::registry* m_pRegistry = nullptr;
};

template <typename... Components, typename... Exclude>
RaycastResult Physics::raycast(RaycastQuery query, entt::exclude_t<Exclude...> exclude) {
	auto boxColliders = m_pRegistry->view<BoxCollider, Transform, Components...>(exclude);

	std::unordered_map<entt::entity, RaycastIntersection> intersections =
		getIntersections<Components...>(query, exclude);

	if (intersections.size() > 0) {
		auto intersection = getMinimumDistanceIntersection(intersections);

		auto optionalEntity = std::make_optional<entt::entity>(intersection.first);
		auto optionalPoint = std::make_optional<glm::vec3>(intersection.second.point);
		auto optionalDistance = std::make_optional<float>(intersection.second.distance);

		return RaycastResult(optionalEntity, optionalPoint, optionalDistance);
	}
	else {
		return RaycastResult(std::nullopt, std::nullopt, std::nullopt);
	}
}

template <typename... Components, typename... Exclude>
std::unordered_map<entt::entity, RaycastIntersection> Physics::getIntersections(
	RaycastQuery query, entt::exclude_t<Exclude...> exclude) {
	auto boxColliders = m_pRegistry->view<BoxCollider, Transform, Components...>(exclude);

	std::unordered_map<entt::entity, RaycastIntersection> intersections;

	for (auto&& [ent, boxCollider, transform] : boxColliders.each()) {
		Ray ray(query.position, query.direction);
		std::optional<RaycastIntersection> raycastResult = ray.getIntersectionWithOBB(boxCollider, transform);

		if (raycastResult.has_value()) {
			intersections.emplace(ent, raycastResult.value());
		}
	}

	return intersections;
}
