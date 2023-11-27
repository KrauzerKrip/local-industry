#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "lc_client/util/image.h"

class Background {
public:
	Background(glm::vec4 color);

	glm::vec4 getColor();
	
private:
	glm::vec4 m_color;
};
