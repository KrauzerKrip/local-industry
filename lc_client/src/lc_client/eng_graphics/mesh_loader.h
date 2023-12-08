#pragma once

#include <entt/entt.hpp>

#include "entt/components.h"


class MeshLoader {
public:
	MeshLoader() {};

	virtual void loadMesh(entt::registry* pUtilRegistry, entt::entity mesh) = 0;

protected: 
};
