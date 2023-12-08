#pragma once

#include <entt/entt.hpp>

#include "cubemap_loader.h"
#include "lc_client/util/eng_resource.h"


class CubemapSystem {
public:
	CubemapSystem(entt::registry* pRegistry, CubemapLoader* pCubemapWork)
		: m_pRegistry(pRegistry),
		  m_pCubemapWork(pCubemapWork){};
	void update();

private:
	entt::registry* m_pRegistry;
	CubemapLoader* m_pCubemapWork;
};
