#pragma once

#include <string>
#include <glm/vec3.hpp>
#include <entt/entt.hpp>

#include "lc_client/eng_script/api/helpers/glm_helpers.h"


struct Properties {
	std::string id;
	std::string uuid;

	Properties() = default;
	Properties(std::string id, std::string uuid) : id(id), uuid(uuid) {}
	Properties(const Properties&) = default;
};

struct Transform {
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	Vec3fHelper getPosition() { return Vec3fHelper(position); }
	void setPosition(Vec3fHelper vector) { position = glm::vec3(vector.x(), vector.y(), vector.z()); }
	Vec3fHelper getScale() { return Vec3fHelper(scale); };
	void setScale(Vec3fHelper vector) { scale = glm::vec3(vector.x(), vector.y(), vector.z()); };

	Transform() : position(glm::vec3(0.0)), scale(glm::vec3(1.0)), rotation(glm::vec3(1.0f, 0.0f, 0.0f)){};
	Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
		: position(position),
		  rotation(rotation),
		  scale(scale) {}
	Transform(const Transform&) = default;
};

struct Parent {
	entt::entity parent;
};
