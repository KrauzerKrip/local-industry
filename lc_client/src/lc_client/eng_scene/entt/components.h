#pragma once 

#include <string>

struct Properties {
	std::string uuid;
	std::string id;

	Properties() = default;
	Properties(std::string uuid, std::string id) : uuid(uuid), id(id) {};
	Properties(const Properties&) = default;
};

struct ModelData {
	std::string id;
	std::string vertexShader;
	std::string fragmentShader;

	std::string colorTexture;
	std::string normalMap;
	std::string aoTexture;
	std::string metallicTexture;
	 
	ModelData() = default;
	ModelData(
		std::string id, std::string vertexShader, std::string fragmentShader, 
		std::string& colorTexture, std::string& normalMap, std::string& aoTexture, std::string& metallicTexture)
		: id(id), vertexShader(vertexShader), fragmentShader(fragmentShader), 
		colorTexture(colorTexture), normalMap(normalMap), aoTexture(aoTexture), metallicTexture(metallicTexture) {};
	ModelData(const ModelData&) = default;
};


