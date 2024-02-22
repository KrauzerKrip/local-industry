#pragma once

#include <string>
#include <optional>

#include "lc_client/util/i_eng_resource.h"


struct ModelData {
	std::string modelFile;
	std::string materialType;
	std::string vertexShader;
	std::string fragmentShader;
	std::optional<std::string> physicsFile;

	ModelData(std::string modelFile, std::string materialType, std::string vertexShader, std::string fragmentShader,
		std::optional<std::string> physicsFile)
		: modelFile(modelFile),
		  materialType(materialType),
		  vertexShader(vertexShader),
		  fragmentShader(fragmentShader),
		  physicsFile(physicsFile) {}
};


class ModelParser {
public:
    ModelParser(eng::IResource* pResource);
	
	[[nodiscard]]
	ModelData parse(const std::string& filePath);

private:
	eng::IResource* m_pResource = nullptr;
};