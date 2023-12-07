#pragma once

#include <string>
#include <glm/glm.hpp>

struct Text {
	std::string text;
	glm::vec2 position;
	float scale;
	glm::vec3 color;
};