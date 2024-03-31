#pragma once

#include <string>

#include <glm/glm.hpp>


class Style {
public:
	virtual glm::vec4 getColor(std::string propertyName) = 0;
	virtual float getBlurIntensity(std::string propertyName) = 0;
};