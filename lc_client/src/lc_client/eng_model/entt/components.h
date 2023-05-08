#pragma once

#include <vector>
#include <iostream>

#include <entt/entt.hpp>

#include "lc_client/eng_graphics/entt/components.h"


struct Model {
	std::vector<entt::entity> meshes;

	Model() = default;
	Model(std::vector<entt::entity> meshes) : meshes(meshes){};
	~Model() {}
	Model(const Model&) = default;
};

struct ModelRequest {
	std::string packName;
	std::string modelName;

	ModelRequest() = default;
	ModelRequest(const std::string packName, const std::string modelName) : packName(packName), modelName(modelName){};
	ModelRequest(const ModelRequest&) = default;
};
