#pragma once

#include <unordered_map>
#include <array>
#include <tuple>

#include <entt/entt.hpp>

#include "model_manager.h"
#include "lc_client/eng_graphics/mesh_loader.h"
#include "model_parser.h"


class ModelSystem {
public:
	ModelSystem(ModelManager* pModelManager, ModelParser* pModelParser, MeshLoader* pMeshWork, entt::registry* pSceneRegistry, entt::registry* pUtilRegistry);

	void update();

private:
	ModelManager* m_pModelManager = nullptr;
	MeshLoader* m_pMeshWork = nullptr;
	ModelParser* m_pModelParser = nullptr;
	entt::registry* m_pSceneRegistry = nullptr;
	entt::registry* m_pUtilRegistry = nullptr;

	std::unordered_map<ModelRequest, std::tuple<Model*, std::string, std::string>> m_loadedModelMap;
};
