#pragma once

#include <entt/entt.hpp>

class GraphicsEntitiesLoading {
public:

	GraphicsEntitiesLoading(
		entt::registry* pMapRegistry, entt::registry* pSceneRegistry) :
		  m_pMapRegistry(pMapRegistry),
		  m_pSceneRegistry(pSceneRegistry) {};
	

	~GraphicsEntitiesLoading() {};

	void loadSceneEntities();
	void loadMapEntities();

private:
	entt::registry* m_pMapRegistry;
	entt::registry* m_pSceneRegistry;
};
