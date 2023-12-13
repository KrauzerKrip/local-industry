#include "ray.h"


Ray::Ray(glm::vec3 origin, glm::vec3 direction) : m_origin(origin), m_direction(direction) {}


std::optional<glm::vec3> Ray::getIntersectionWithAABB(BoxCollider boxCollider, glm::vec3 boxPosition) {
	glm::vec3 size = glm::vec3(boxCollider.length, boxCollider.height, boxCollider.width) * 0.5f;

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

	glm::vec3 intersection = m_origin + (m_direction * maxT);

	for (int i = 0; i < 3; i++) {
		if ((intersection[i] + m_epsilon < boxMin[i]) || (intersection[i] - m_epsilon > boxMax[i])) {
			return std::nullopt;
		}
	}

	return std::make_optional<glm::vec3>(intersection);
}

std::optional<glm::vec3> Ray::getIntersectionWithOBB(BoxCollider boxCollider, Transform transform) {
	glm::qua boxOrientation = transform.rotation;
	glm::vec3 boxPosition = transform.position;

	glm::mat3 transformMatrix = glm::mat3(boxOrientation);

	glm::mat3 inverseTransform = glm::mat3(glm::conjugate(boxOrientation)); 

	glm::vec3 localRayPos = m_origin - boxPosition;

	Ray aabbRay(inverseTransform * localRayPos, inverseTransform * m_direction);

	std::optional<glm::vec3> result = aabbRay.getIntersectionWithAABB(boxCollider, glm::vec3(0));

	if (result.has_value()) {
		glm::vec3 collisionPosition = transformMatrix * result.value() + boxPosition;
		return collisionPosition;
	}
	else {
		return std::nullopt;
	}
}