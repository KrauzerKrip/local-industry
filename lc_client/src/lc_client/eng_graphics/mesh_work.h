#pragma once

#include <entt/entt.hpp>

#include "entt/components.h"


class MeshWork {
public:
	MeshWork(entt::registry* pUtilRegistry) : m_pUtilRegistry(pUtilRegistry){};

	virtual void loadMesh(entt::entity mesh) = 0;

protected: 
	entt::registry* m_pUtilRegistry;
};
