#pragma once

#include <entt/entt.hpp>

#include "cubemap_loader.h"
#include "lc_client/util/i_eng_resource.h"


class CubemapWork {
public:
	CubemapWork(eng::IResource* pResource) : m_pResource(pResource) {};

	virtual void loadCubemap(entt::registry* pRegistry, entt::entity entity, std::string path) = 0;

protected: 
	eng::IResource* m_pResource;
};
