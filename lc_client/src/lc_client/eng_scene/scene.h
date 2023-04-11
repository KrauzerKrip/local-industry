#pragma once

#include <string>
#include <entt/entt.hpp>

#include "lc_client/eng_procedures/i_shaders.h"
#include "lc_client/eng_procedures/graphics_entities_loading.h"
#include "lc_client/util/i_eng_resource.h"
#include "lc_client/eng_procedures/openGL/gl_texture_manager.h"
#include "lc_client/eng_scene/scene_loading.h"

class GraphicsEntitiesLoading;

struct SceneDependencies {
	IShaderManager* pShaderManager;
	GraphicsEntitiesLoading* pGraphicsEntitiesLoading;
	eng::IResource* pResource;
};

class Scene {
public:
	Scene();
	~Scene();

	void loadScene(std::string pack, std::string scene);
	void setDependencies(SceneDependencies& sceneDependencies);
	entt::registry& getMapRegistry();
	entt::registry& getSceneRegistry();
	entt::registry& getUtilRegistry();

private:
	entt::registry m_mapRegistry;
	entt::registry m_sceneRegistry;
	entt::registry m_utilRegistry;

	std::string m_name;
	std::string m_pack;

	TextureManager* m_pTextureManager = nullptr;
	
	SceneLoading* m_pSceneLoading = nullptr;
	IShaderManager* m_pShaderManager = nullptr;
	GraphicsEntitiesLoading* m_pGraphicsEntitiesLoading = nullptr;
	eng::IResource* m_pResource = nullptr;
};