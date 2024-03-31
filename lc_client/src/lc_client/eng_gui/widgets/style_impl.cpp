#include "style_impl.h"

glm::vec4 StyleImpl::getColor(std::string propertyName) { return m_colors.at(propertyName); }

float StyleImpl::getBlurIntensity(std::string propertyName) { return m_blurIntensities.at(propertyName); }

void StyleImpl::setColor(std::string propertyName, glm::vec4 color) { m_colors[propertyName] = color; }

void StyleImpl::setColor(std::string propertyName, unsigned int r, unsigned int g, unsigned int b, unsigned int a) {
	m_colors[propertyName] = glm::vec4(static_cast<float>(r) / 255.0f, static_cast<float>(g) / 255.0f,
		static_cast<float>(b) / 255.0f, static_cast<float>(a) / 255.0f);
}

void StyleImpl::setBlurIntensitry(std::string propertyName, float blurIntensity) {
	m_blurIntensities[propertyName] = blurIntensity;
}
