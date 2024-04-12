#pragma once

#include <vector>
#include <iostream>

#include <entt/entt.hpp>

#include "lc_client/eng_graphics/entt/components.h"


struct Model {
	std::vector<entt::entity> meshes;
	std::string materialDir;
	std::string materialType;

	Model() = default;
	Model(std::vector<entt::entity> meshes) : meshes(meshes){};
	~Model() {}
	Model(const Model&) = default;
};

struct ModelRequest {
	std::string packName;
	std::string modelName;
	bool loadShaders;

	ModelRequest() = default;
	ModelRequest(const std::string packName, const std::string modelName, bool loadShaders = true)
		: packName(packName),
		  modelName(modelName),
		loadShaders(loadShaders)
	{};
	ModelRequest(const ModelRequest&) = default;
	bool operator==(const ModelRequest& other) const {
		return ((packName == other.packName) && (modelName == other.modelName));
	}
};




struct ModelReloadRequest {

};

struct MeshLoadRequest {

};

struct MeshUnloadRequest {

};

template <> struct std::hash<ModelRequest> {
	std::size_t operator()(const ModelRequest& k) const {
		using std::size_t;
		using std::hash;
		using std::string;

		std::size_t res = 17;
		res = res * 31 + hash<string>()(k.packName);
		res = res * 31 + hash<string>()(k.modelName);

		return res;
	}
};
