#pragma once

#include <string>
#include <entt/entt.hpp>

#include "lc_client/eng_procedures/i_shaders.h"

class Scene {
public:
	Scene();
	~Scene();

	void loadScene(std::string name);
	void setShaderManager(IShaderManager* pShaderManager);
	entt::registry* getMapRegistry();
	entt::registry* getSceneRegistry();

private:
	entt::registry m_mapRegistry;
	entt::registry m_sceneRegistry;

	std::string m_name;

	IShaderManager* m_pShaderManager = nullptr;
};
