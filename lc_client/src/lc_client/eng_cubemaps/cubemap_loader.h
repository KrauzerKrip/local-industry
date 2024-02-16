#pragma once

#include <entt/entt.hpp>

#include "cubemap_loader.h"
#include "lc_client/util/i_eng_resource.h"


class CubemapLoader {
public:
	CubemapLoader(eng::IResource* pResource)
		: m_pResource(pResource) {}
	virtual ~CubemapLoader() = default;

	virtual void loadCubemap(
		entt::entity entity, std::string path, entt::registry* pRegistry, entt::registry* pUtilRegistry) = 0;

protected: 
	eng::IResource* m_pResource = nullptr;
};
