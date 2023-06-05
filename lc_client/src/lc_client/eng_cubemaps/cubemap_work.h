#pragma once

#include <entt/entt.hpp>

#include "cubemap_loader.h"
#include "lc_client/util/i_eng_resource.h"


class CubemapWork {
public:
	CubemapWork(entt::registry* pRegistry, eng::IResource* pResource) : m_pRegistry(pRegistry), m_pResource(pResource) {};

	virtual void loadCubemap(entt::entity entity, std::string path) = 0;

protected: 
	entt::registry* m_pRegistry;
	eng::IResource* m_pResource;
};
