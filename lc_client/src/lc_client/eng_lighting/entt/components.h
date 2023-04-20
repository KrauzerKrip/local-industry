#pragma once

#include <glm/glm.hpp>
#include <entt/entt.hpp>

struct AmbientLight {

};

struct PointLight {
	glm::vec3 relativePosition;
	entt::entity parentEntity;
};

struct DirectionalLight {

};

struct SpotLight {

};
