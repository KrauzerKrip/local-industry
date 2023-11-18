#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "lc_client/util/image.h"

class Background {
public:
	Background(glm::vec3 color);

	glm::vec3 getColor();
	
private:
	glm::vec3 m_color;
};
