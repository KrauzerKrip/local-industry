#pragma once 

#include <string>
#include <glm/vec3.hpp>

struct Properties {
	std::string uuid;
	std::string id;

	Properties() = default;
	Properties(std::string uuid, std::string id) : uuid(uuid), id(id) {};
	Properties(const Properties&) = default;
};

struct Transform {
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	Transform() = default;
	Transform(const Transform&) = default;
};

struct ModelData {
	const std::string id;
	const std::string path;
	const std::string texturesPath;
	const std::string vertexShader;
	const std::string fragmentShader;
	 
	ModelData() = default;
	ModelData(
		const std::string id, const std::string path, const std::string texturesPath, const std::string vertexShader, const std::string fragmentShader)
		: id(id), path(path), texturesPath(texturesPath), vertexShader(vertexShader), fragmentShader(fragmentShader) {};
	ModelData(const ModelData&) = default;
};


