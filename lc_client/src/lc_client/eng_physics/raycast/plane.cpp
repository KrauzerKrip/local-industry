#include "plane.h"


Plane::Plane(glm::vec3 pointA, glm::vec3 pointB, glm::vec3 pointC) : m_pointA(pointA), m_pointB(pointB), m_pointC(pointC) {
}

glm::vec3 Plane::getNormal() { 
	glm::vec3 AB = m_pointB - m_pointA;
	glm::vec3 AC = m_pointC - m_pointA;

	glm::vec3 normal = glm::normalize(glm::cross(AB, AC));
	
	return normal;
}

std::optional<glm::vec3> Plane::getIntersectionWithLine(glm::vec3 linePoint, glm::vec3 lineDirection) {
	glm::vec3 planeNormal = getNormal();

	if (glm::dot(planeNormal, lineDirection) == 0) {
		return std::nullopt;
	}

//	A = y1 (z2 - z3) + y2 (z3 - z1) + y3 (z1 - z2)
//	B = z1 (x2 - x3) + z2 (x3 - x1) + z3 (x1 - x2)
//	C = x1 (y2 - y3) + x2 (y3 - y1) + x3 (y1 - y2)
//	D = -x1 (y2 z3 - y3 z2) - x2 (y3 z1 - y1 z3) - x3 (y1 z2 - y2 z1)

	glm::vec3 p1 = m_pointA;
	glm::vec3 p2 = m_pointB;
	glm::vec3 p3 = m_pointC;
	
	float A = p1.y * (p2.z - p3.z) + p2.y * (p3.z - p1.z) + p3.y * (p1.z - p2.z);
	float B = p1.z * (p2.x - p3.x) + p2.z * (p3.x - p1.x) + p3.z * (p1.x - p2.x);
	float C = p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y);
	float D = -p1.x * (p2.y * p3.z - p3.y * p2.z) - p2.x * (p3.y * p1.z - p1.y * p3.z) - p3.x * (p1.y * p2.z - p2.y * p1.z);

	float x0 = linePoint.x;
	float y0 = linePoint.y;
	float z0 = linePoint.z;

	float l = lineDirection.x;
	float m = lineDirection.y;
	float p = lineDirection.z;

	float t = (A * x0 + B * y0 + C * z0 - D) / (-A * l - B * m - C * p);

	float x = x0 + l * t;
	float y = y0 * m * t;
	float z = z0 * p * t;

	return std::make_optional<glm::vec3>(glm::vec3(x, y, z));
}
