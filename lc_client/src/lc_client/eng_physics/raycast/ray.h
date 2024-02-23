#pragma once

#include <optional>

#include <glm/glm.hpp>

#include "lc_client/eng_physics/entt/components.h"
#include "lc_client/eng_scene/entt/components.h"


struct RaycastIntersection {
	glm::vec3 point;
	float distance;

	RaycastIntersection(glm::vec3 point, float distance) : point(point), distance(distance) {}
	RaycastIntersection(){}
};


class Ray {
public:
	Ray(glm::vec3 origin, glm::vec3 direction);

	std::optional<RaycastIntersection> getIntersectionWithAABB(glm::vec3 boxPosition, glm::vec3 boxSize);
	std::optional<RaycastIntersection> getIntersectionWithOBB(const Transform& boxTransform);

private:
	glm::vec3 m_origin;
	glm::vec3 m_direction;

	const float m_epsilon = 0.0001;
};
