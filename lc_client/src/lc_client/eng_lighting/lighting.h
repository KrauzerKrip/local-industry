#pragma once

#include <glm/glm.hpp>

class AmbientLight;

class Lighting {
public:
	Lighting();
	~Lighting() = default;

	AmbientLight& getAmbientLight();
	
private:
	AmbientLight m_ambientLight;
};

class AmbientLight {
public:
	AmbientLight() = default;
	~AmbientLight() = default;

	glm::vec3 getColor();
	void setColor(glm::vec3 color);
	float getStrength();
	void setStrength(float strength);
	
private:
	glm::vec3 m_color;
	float m_strength;
};
