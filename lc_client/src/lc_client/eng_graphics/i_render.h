#pragma once

#include <vector>
#include <entt/entt.hpp>

class IRender {
public:
	virtual ~IRender() {};

	virtual void init() = 0;
	virtual void render(std::vector<entt::entity>* pGraphicsEntities) = 0;
	virtual void clear() = 0;
	virtual void cleanUp() = 0;
};