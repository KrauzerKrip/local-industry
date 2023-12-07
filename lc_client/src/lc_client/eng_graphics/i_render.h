#pragma once

#include <vector>
#include <entt/entt.hpp>

#include "lc_client/eng_scene/scene.h" 
#include "lc_client/eng_scene/skybox.h"
#include "lc_client/eng_map/map.h"

class IRender {
public:
	virtual ~IRender() {};

	virtual void init() = 0;
	virtual void render() = 0;
	virtual void clear() = 0;
	virtual void cleanUp() = 0;
	virtual void setDependecies(Map* pMap, Scene* m_pScene, Skybox* pSkybox) = 0;
};