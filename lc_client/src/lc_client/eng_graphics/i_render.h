#pragma once

#include <vector>
#include <entt/entt.hpp>

#include "lc_client/eng_world/world.h" 


class IRender {
public:
	virtual ~IRender() {};

	virtual void init() = 0;
	virtual void render() = 0;
	virtual void clear() = 0;
	virtual void cleanUp() = 0;
};