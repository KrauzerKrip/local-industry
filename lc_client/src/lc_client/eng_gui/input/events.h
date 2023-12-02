#pragma once

#include <glm/glm.hpp>
#include <string>


struct MouseClickEvent {
	glm::vec2 position;
	std::string button;

	MouseClickEvent(glm::vec2 position, std::string button) : position(position), button(button){};
};

struct KeyEvent {
	std::string key;
};
