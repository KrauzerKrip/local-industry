#pragma once

#include <vector>
#include <entt/entt.hpp>

class IRender {
public:
	virtual ~IRender() {};

	virtual void init() = 0;
	virtual void render() = 0;
	virtual void clear() = 0;
	virtual void cleanUp() = 0;
	virtual void setRegistries(entt::registry& pMapRegistry, entt::registry& pSceneRegistry, entt::registry& pUtilRegistry) = 0;
};