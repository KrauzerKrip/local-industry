#pragma once

#include <string>
#include <entt/entt.hpp>

#include "lc_client/eng_procedures/i_shaders.h"
#include "lc_client/eng_procedures/i_graphics_entities_loading.h"
#include "lc_client/util/i_eng_resource.h"
#include "lc_client/eng_procedures/openGL/gl_texture_manager.h"

struct SceneDependencies {
	IShaderManager* pShaderManager;
	IGraphicsEntitiesLoading* pGraphicsEntitiesLoading;
	eng::IResource* pResource;
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

	TextureManager* m_pTextureManager = nullptr;

	IShaderManager* m_pShaderManager = nullptr;
	IGraphicsEntitiesLoading* m_pGraphicsEntitiesLoading = nullptr;
	eng::IResource* m_pResource;
};