#pragma once

#include <unordered_map>
#include <array>

#include <entt/entt.hpp>

#include "model_manager.h"
#include "lc_client/eng_graphics/mesh_work.h"


class ModelSystem {
public:
	ModelSystem(ModelManager* pModelManager, MeshWork* pMeshWork, entt::registry* pSceneRegistry);

	void update();

private:
	ModelManager* m_pModelManager = nullptr;
	MeshWork* m_pMeshWork = nullptr;
	entt::registry* m_pSceneRegistry = nullptr;

	std::unordered_map<ModelRequest, Model*> m_loadedModelMap;
};
