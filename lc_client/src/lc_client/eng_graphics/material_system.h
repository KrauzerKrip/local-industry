#pragma once

#include <entt/entt.hpp>

#include "entt/components.h"


class MaterialSystem {
public:
	MaterialSystem(entt::registry* pUtilRegistry);

	void loadMaterials();
	void unloadMaterials();
	

private:

	entt::registry* m_pUtilRegistry;
};
