#include "skybox.h"
#include "skybox.h"
#include "skybox.h"
#include "skybox.h"
#include "skybox.h"
#include "skybox.h"

Skybox::Skybox(SkyboxRender* pSkyboxRender) : m_lightColor(glm::vec3()), m_lightStrength(1.0f) { m_pSkyboxRender = pSkyboxRender; }

void Skybox::render(glm::mat4& projection, glm::mat4& view) { m_pSkyboxRender->render(projection, view); }

glm::vec3 Skybox::getLightColor() const { return m_lightColor; }

void Skybox::setLightColor(glm::vec3 color) { m_lightColor = color; }

void Skybox::setLightColor(float r, float g, float b) {
	m_lightColor.r = r;
	m_lightColor.g = g;
	m_lightColor.b = b;
}

void Skybox::setLightColor(glm::uvec3 color) {
	const float i = 255.0f;
	m_lightColor = glm::vec3(color.r / i, color.g / i, color.b / i);
}

void Skybox::setLightColor(int r, int g, int b) { setLightColor(glm::uvec3(r, g, b)); }

float Skybox::getLightStrength() { return m_lightStrength; }

void Skybox::setLightStrength(float strength) { m_lightStrength = strength; }
