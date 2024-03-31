#pragma once

#include <unordered_map>
#include <string>

#include <glm/glm.hpp>

#include "style.h"


class StyleImpl : public Style {
public:
	glm::vec4 getColor(std::string propertyName) override;
	float getBlurIntensity(std::string propertyName) override;

	void setColor(std::string propertyName, glm::vec4 color);
	void setColor(std::string propertyName, unsigned int r, unsigned int g, unsigned int b, unsigned int a);
	void setBlurIntensitry(std::string propertyName, float blurIntensity);
	
private:
	std::unordered_map<std::string, glm::vec4> m_colors;
	std::unordered_map<std::string, float> m_blurIntensities;
};