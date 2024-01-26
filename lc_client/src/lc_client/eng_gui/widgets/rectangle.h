#pragma once

#include <glm/glm.hpp>

struct RectangleVertices {
	glm::vec2 bottomLeft;
	glm::vec2 topLeft;
	glm::vec2 topRight;
	glm::vec2 bottomRight;
};


class Rectangle {
public:
	Rectangle();

	bool isPointIntersecting(glm::vec2 point) const;
	RectangleVertices getVertices() const; 
	
	glm::vec2 m_absolutePosition;
	glm::vec2 m_size;
};
