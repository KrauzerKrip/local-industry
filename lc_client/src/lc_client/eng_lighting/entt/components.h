#pragma once

#include <glm/glm.hpp>
#include <entt/entt.hpp>


struct PointLight {
	glm::vec3 relativePosition;
	glm::vec3 color;
	//float power; / float luminance;
	entt::entity parentEntity;
};

struct DirectionalLight {

};

struct SpotLight {

};
