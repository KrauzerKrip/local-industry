#pragma once

#include <glm/glm.hpp>

#include "lc_client/eng_graphics/skybox_render.h"
#include "lc_client/eng_cubemaps/cubemap_loader.h"
#include "lc_client/util/i_eng_resource.h"


class SkyboxSystem {
public:
	SkyboxSystem(SkyboxRender* pSkyboxRender, entt::registry* pRegistry, eng::IResource* pResource);
	~SkyboxSystem() = default;

	void update();

private:
	void loadSkybox(std::string pack, std::string name);

	SkyboxRender* m_pSkyboxRender = nullptr;
	eng::IResource* m_pResource = nullptr;
	entt::registry* m_pRegistry = nullptr;
};