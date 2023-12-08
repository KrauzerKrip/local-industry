#pragma once

#include <memory>
#include <string>
#include <entt/entt.hpp>

#include "lc_client/eng_cubemaps/cubemap_loader.h"
#include "lc_client/eng_cubemaps/cubemap_texture_loader.h"


class CubemapLoaderGl : public CubemapLoader {
public:
	CubemapLoaderGl(eng::IResource* pResource) : CubemapLoader(pResource){};

	void loadCubemap(entt::registry* pRegistry, entt::entity entity, std::string path); 

private:
	unsigned int getTexture(std::unique_ptr<CubemapMaterial> material);
};
