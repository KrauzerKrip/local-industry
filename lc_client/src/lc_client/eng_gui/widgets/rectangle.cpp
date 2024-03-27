#include "rectangle.h"

Rectangle::Rectangle() { 
	m_absolutePosition = glm::vec2(0);
	m_size = glm::vec2(0);
}

bool Rectangle::isPointIntersecting(glm::vec2 point) const { 
	if (point.x > m_absolutePosition.x && point.x < m_absolutePosition.x + m_size.x) {
		if ((point.y - 0) > m_absolutePosition.y && (point.y - 0) < m_absolutePosition.y + m_size.y) {
			return true;
		}
	}

	return false; 
}

RectangleVertices Rectangle::getVertices() const { 
	RectangleVertices vertices;

	vertices.bottomLeft = m_absolutePosition;
	vertices.topLeft = glm::vec2(m_absolutePosition.x, m_absolutePosition.y + m_size.y);
	vertices.topRight =
		glm::vec2(m_absolutePosition.x + m_size.x, m_absolutePosition.y + m_size.y);
	vertices.bottomRight = glm::vec2(m_absolutePosition.x + m_size.x, m_absolutePosition.y);

	return vertices;
}

