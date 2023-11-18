#include "background.h"

Background::Background(glm::vec3 color) { m_color = color; }

glm::vec3 Background::getColor() { return m_color; }
