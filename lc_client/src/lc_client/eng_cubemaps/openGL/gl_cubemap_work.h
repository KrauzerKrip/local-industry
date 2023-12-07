#pragma once

#include <memory>
#include <string>

#include "lc_client/eng_cubemaps/cubemap_work.h"


class CubemapWorkGl : public CubemapWork {
public:
	CubemapWorkGl(eng::IResource* pResource) : CubemapWork(pResource){};

	void loadCubemap(entt::registry* pRegistry, entt::entity entity, std::string path); 

private:
	unsigned int getTexture(std::unique_ptr<CubemapMaterial> material);
};
