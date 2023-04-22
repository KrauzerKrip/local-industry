#include "skybox.h"
#include "skybox.h"
#include "skybox.h"
#include "skybox.h"

glm::vec3 Skybox::getLightColor() const { return m_lightColor; }

void Skybox::setLightColor(glm::vec3 color) { m_lightColor = color; }

void Skybox::setLightColor(float r, float g, float b) {
	m_lightColor.r = r;
	m_lightColor.g = g;
	m_lightColor.b = b;
}

void Skybox::setLightColor(glm::uvec3 color) {
	unsigned int i = 255;
	m_lightColor = color / i;
}

void Skybox::setLightColor(int r, int g, int b) { setLightColor(glm::uvec3(r, g, b)); }

float Skybox::getLightStrength() { return m_lightStrength; }

void Skybox::setLightStrength(float strength) { m_lightStrength = strength; }