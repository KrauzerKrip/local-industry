#pragma once

#include <glm/glm.hpp>


class Skybox {
public:
	Skybox() = default;
	~Skybox() = default;

	glm::vec3 getLightColor() const;
	void setLightColor(glm::vec3 color);
	void setLightColor(float r, float g, float b);
	void setLightColor(glm::uvec3 color);
	void setLightColor(int r, int g, int b);
	float getLightStrength();
	void setLightStrength(float strength);

private:
	glm::vec3 m_lightColor;
	float m_lightStrength;
};