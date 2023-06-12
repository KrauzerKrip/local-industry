#pragma once

#include <glm/glm.hpp>


class Vec3fHelper {
public:
	Vec3fHelper(glm::vec3& vector) : m_vector(vector){};

	float x() const { return m_vector.x; };

	float y() const { return m_vector.y; };

	float z() const { return m_vector.z; };

	void setX(float x) { m_vector.x = x; }

	void setY(float y) { m_vector.y = y; }

	void setZ(float z) { m_vector.z = z; }

	void setXYZ(float x, float y, float z) {
		m_vector.x = x;
		m_vector.y = y;
		m_vector.z = z;
	}

private:
	glm::vec3& m_vector;
};
