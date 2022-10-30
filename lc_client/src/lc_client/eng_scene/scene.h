#pragma once

#include <string>
#include <entt/entt.hpp>

#include "lc_client/eng_procedures/i_shaders.h"
#include "lc_client/eng_procedures/i_graphics_entities_loading.h"

struct SceneDependencies {
	IShaderManager* pShaderManager;
	IGraphicsEntitiesLoading* pGraphicsEntitiesLoading;
};


class Scene {
public:
	Scene();
	~Scene();

	void loadScene(std::string name);
	void setDependencies(SceneDependencies& sceneDependencies);
	entt::registry* getMapRegistry();
	entt::registry* getSceneRegistry();

private:
	entt::registry m_mapRegistry;
	entt::registry m_sceneRegistry;

	std::string m_name;

	IShaderManager* m_pShaderManager = nullptr;
	IGraphicsEntitiesLoading* m_pGraphicsEntitiesLoading = nullptr;
};