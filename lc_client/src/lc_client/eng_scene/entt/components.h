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
	std::string id;
	std::string vertexShader;
	std::string fragmentShader;

	std::string colorTexture = "";
	std::string normalMap = "";
	std::string aoTexture = "";
	std::string metallicTexture = "";
	 
	ModelData() = default;
	ModelData(
		std::string id, std::string vertexShader, std::string fragmentShader, 
		std::string& colorTexture, std::string& normalMap, std::string& aoTexture, std::string& metallicTexture)
		: id(id), vertexShader(vertexShader), fragmentShader(fragmentShader), 
		colorTexture(colorTexture), normalMap(normalMap), aoTexture(aoTexture), metallicTexture(metallicTexture) {};
	ModelData(const ModelData&) = default;
};


