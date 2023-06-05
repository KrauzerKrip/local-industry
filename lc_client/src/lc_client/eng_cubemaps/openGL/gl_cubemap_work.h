#pragma once

#include <memory>
#include <string>

#include "lc_client/eng_cubemaps/cubemap_work.h"


class CubemapWorkGl : public CubemapWork {
public:
	CubemapWorkGl(entt::registry* pRegistry, eng::IResource* pResource) : CubemapWork(pRegistry, pResource){};

	void loadCubemap(entt::entity entity, std::string path); 

private:
	unsigned int getTexture(std::unique_ptr<CubemapMaterial> material);
};
