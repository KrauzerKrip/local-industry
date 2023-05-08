#pragma once

#include <string>
#include <glm/vec3.hpp>
#include <entt/entt.hpp>

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

	Transform() : scale(glm::vec3(1.0)){};
	Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
		: position(position),
		  rotation(rotation),
		  scale(scale) {}
	Transform(const Transform&) = default;
};

struct Parent {
	entt::entity parent;
};

struct ModelData {
	std::string packName;
	std::string modelName;

	ModelData() = default;
	ModelData(const std::string packName, const std::string modelName) : packName(packName), modelName(modelName){};
	ModelData(const ModelData&) = default;
};
