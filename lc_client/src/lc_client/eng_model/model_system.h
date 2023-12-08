#pragma once

#include <unordered_map>
#include <array>

#include <entt/entt.hpp>

#include "model_manager.h"
#include "lc_client/eng_graphics/mesh_loader.h"


class ModelSystem {
public:
	ModelSystem(ModelManager* pModelManager, MeshLoader* pMeshWork, entt::registry* pSceneRegistry, entt::registry* pUtilRegistry);

	void update();

private:
	ModelManager* m_pModelManager = nullptr;
	MeshLoader* m_pMeshWork = nullptr;
	entt::registry* m_pSceneRegistry = nullptr;
	entt::registry* m_pUtilRegistry = nullptr;

	std::unordered_map<ModelRequest, Model*> m_loadedModelMap;
};
