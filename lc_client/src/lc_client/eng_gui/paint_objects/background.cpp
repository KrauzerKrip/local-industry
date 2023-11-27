#include "background.h"

Background::Background(glm::vec4 color) { m_color = color; }

glm::vec4 Background::getColor() { return m_color; }
