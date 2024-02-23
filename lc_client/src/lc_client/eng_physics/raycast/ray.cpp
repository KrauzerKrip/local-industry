#include "ray.h"

#include <iostream>


Ray::Ray(glm::vec3 origin, glm::vec3 direction) : m_origin(origin), m_direction(direction) {}


std::optional<RaycastIntersection> Ray::getIntersectionWithAABB(glm::vec3 boxPosition, glm::vec3 boxSize) {
	glm::vec3 size = boxSize;

	glm::vec3 boxMin = boxPosition - size;
	glm::vec3 boxMax = boxPosition + size;	
	
	glm::vec3 tVals = glm::vec3(-1, -1, -1);

	for (int i = 0; i < 3; i++) {
		if (m_direction[i] > 0) {
			tVals[i] = (boxMin[i] - m_origin[i]) / m_direction[i];
		}
		else if (m_direction[i] < 0) {
			tVals[i] = (boxMax[i] - m_origin[i]) / m_direction[i];
		}
	}

	float maxT = std::max(tVals.x, std::max(tVals.y, tVals.z));

	if (maxT < 0.0) {
		return std::nullopt;
	}

	glm::vec3 intersectionPoint = m_origin + (m_direction * maxT);

	for (int i = 0; i < 3; i++) {
		if ((intersectionPoint[i] + m_epsilon < boxMin[i]) || (intersectionPoint[i] - m_epsilon > boxMax[i])) {
			return std::nullopt;
		}
	}

	return std::make_optional<RaycastIntersection>(RaycastIntersection(intersectionPoint, maxT));
}

std::optional<RaycastIntersection> Ray::getIntersectionWithOBB(const Transform& boxTransform) {
	glm::qua boxOrientation = boxTransform.rotation;
	glm::vec3 boxPosition = boxTransform.position;

	glm::mat3 transformMatrix = glm::mat3(boxOrientation);

	glm::mat3 inverseTransform = glm::mat3(glm::conjugate(boxOrientation)); 

	glm::vec3 localRayPos = m_origin - boxPosition;

	Ray aabbRay(inverseTransform * localRayPos, inverseTransform * m_direction);

	std::optional<RaycastIntersection> result = aabbRay.getIntersectionWithAABB(glm::vec3(0), boxTransform.scale);

	if (result.has_value()) {
		glm::vec3 intersectionPoint = transformMatrix * result.value().point + boxPosition;
		return std::make_optional<RaycastIntersection>(RaycastIntersection(intersectionPoint, result.value().distance));
	}
	else {
		return std::nullopt;
	}
}