#pragma once

#include <entt/entt.hpp>

#include "entt/components.h"
#include "lc_client/eng_graphics/texture_manager.h"


class MaterialSystem {
public:
	MaterialSystem(TextureManager* pTextureManager, entt::registry* m_pRegistry, entt::registry* pUtilRegistry);

	void update();
	void loadMaterials();
	void unloadMaterials();

private:
	MaterialMR getMaterialMr(std::string dir);
	MaterialSG getMaterialSg(std::string dir);

	TextureManager* m_pTextureManager = nullptr;

	entt::registry* m_pRegistry = nullptr;
	entt::registry* m_pUtilRegistry = nullptr;
};
