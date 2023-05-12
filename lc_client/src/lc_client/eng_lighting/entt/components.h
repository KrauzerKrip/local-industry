#pragma once

#include <glm/glm.hpp>
#include <entt/entt.hpp>


struct PointLight {
	glm::vec3 color;
	//float power; // float luminance;
	void setColor(int r, int g, int b) { 
		float i = 255.0;
		color.r = r / i;
		color.g = g / i;
		color.b = b / i;
	}
};

struct DirectionalLight {

};

struct SpotLight {

};
