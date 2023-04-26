#pragma once

#include <entt/entt.hpp>

#include "lc_client/eng_graphics/graphics_entities_util.h"

class GraphicsEntitiesLoading {
public:

	GraphicsEntitiesLoading(GraphicsEntitiesUtil* pGraphicsEntitiesUtil, 
		entt::registry* pMapRegistry, entt::registry* pSceneRegistry)
		: m_pGraphicsEntitiesUtil(pGraphicsEntitiesUtil),
		  m_pMapRegistry(pMapRegistry),
		  m_pSceneRegistry(pSceneRegistry) {};
	

	~GraphicsEntitiesLoading() {};

	void loadSceneEntities();
	void loadMapEntities();

private:
	GraphicsEntitiesUtil* m_pGraphicsEntitiesUtil;
	entt::registry* m_pMapRegistry;
	entt::registry* m_pSceneRegistry;
};
