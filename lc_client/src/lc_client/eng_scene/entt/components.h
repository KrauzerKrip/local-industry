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
	std::string modelId;
	std::string vertexShader;
	std::string fragmentShader;

	ModelData() = default;
	ModelData(std::string modelId, std::string vertexShader, std::string fragmentShader)
		: modelId(modelId), vertexShader(vertexShader), fragmentShader(fragmentShader) {};
	ModelData(const ModelData&) = default;
};


