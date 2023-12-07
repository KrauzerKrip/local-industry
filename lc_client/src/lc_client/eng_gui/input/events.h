#pragma once

#include <glm/glm.hpp>
#include <string>

#include "lc_client/eng_input/key_code.h"


struct MouseClickEvent {
	glm::vec2 position;
	KeyCode button;

	MouseClickEvent(glm::vec2 position, KeyCode button) : position(position), button(button){};
};

struct KeyEvent {
	KeyCode key;
};
