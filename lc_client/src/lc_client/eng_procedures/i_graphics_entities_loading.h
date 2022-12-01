  #pragma once

#include <entt/entt.hpp>

class IGraphicsEntitiesLoading {
public:
	virtual ~IGraphicsEntitiesLoading() {};

	virtual void loadSceneEntities(entt::registry* registry) = 0;
	virtual void loadMapEntities(entt::registry* registry) = 0;
};
