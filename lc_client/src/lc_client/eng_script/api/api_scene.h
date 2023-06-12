#pragma once

#include <entt/entt.hpp>

#include "lc_client/eng_scene/entt/components.h"
#include "helpers/components.h"
#include "lc_client/eng_lighting/entt/components.h"
#include "helpers/registry_helper.h"


class SceneApi {
public:
	SceneApi(entt::registry* pSceneRegistry);

	RegistryHelper& getRegistry();

	TransformHelper addTranfsorm(entt::id_type ent);
	PointLight& addPointLight(entt::id_type ent);

	void requestModel(entt::id_type ent, std::string packName, std::string modelName);

private:
	entt::registry* m_pRegistry;
	RegistryHelper m_registryHelper;

	entt::entity constructEntity(entt::id_type ent);
};
