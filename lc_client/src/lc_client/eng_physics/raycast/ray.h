#pragma once

#include <optional>

#include <glm/glm.hpp>

#include "lc_client/eng_physics/entt/components.h"
#include "lc_client/eng_scene/entt/components.h"


class Ray {
public:
	Ray(glm::vec3 origin, glm::vec3 direction);

	std::optional<glm::vec3> getIntersectionWithAABB(BoxCollider boxCollider, glm::vec3 boxPosition);
	std::optional<glm::vec3> getIntersectionWithOBB(BoxCollider boxCollider, Transform transform);

private:
	glm::vec3 m_origin;
	glm::vec3 m_direction;

	const float m_epsilon = 0.0001;
};
