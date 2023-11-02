#pragma once

#include <entt/entt.hpp>

#include "entt/components.h"


class MeshWork {
public:
	MeshWork() {};

	virtual void loadMesh(entt::registry* pUtilRegistry, entt::entity mesh) = 0;

protected: 
};
