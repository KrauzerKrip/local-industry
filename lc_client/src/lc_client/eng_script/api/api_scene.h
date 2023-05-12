#pragma once

#include <entt/entt.hpp>

#include "lc_client/eng_scene/entt/components.h"
#include "lc_client/eng_script/api/helpers/components.h"
#include "lc_client/eng_lighting/entt/components.h"


class SceneApi {
public:
	SceneApi();

	TransformHelper addTranfsorm(entt::id_type ent);
	PointLight& addPointLight(entt::id_type ent);

	void requestModel(entt::id_type ent, std::string packName, std::string modelName);

private:
	entt::registry* m_pRegistry;

	entt::entity constructEntity(entt::id_type ent);
};
