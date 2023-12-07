#pragma once

#include <entt/entt.hpp>

#include "lc_client/eng_scene/entt/components.h"
#include "lc_client/eng_lighting/entt/components.h"
#include "helpers/registry_helper.h"


class SceneApi {
public:
	SceneApi(entt::registry* pSceneRegistry);

	RegistryHelper& getRegistry();

private:
	entt::registry* m_pRegistry;
	RegistryHelper m_registryHelper;

	entt::entity constructEntity(entt::id_type ent);
};
