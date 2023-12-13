#pragma once

#include <optional>
#include <glm/glm.hpp>


class Plane {
public:
	Plane(glm::vec3 pointA, glm::vec3 pointB, glm::vec3 pointC);

	glm::vec3 getNormal();
	std::optional<glm::vec3> getIntersectionWithLine(glm::vec3 linePoint, glm::vec3 lineDirection);

private:
	glm::vec3 m_pointA;
	glm::vec3 m_pointB;
	glm::vec3 m_pointC;
};
