#pragma once

#include <entt/entt.hpp>

#include "lc_client/eng_graphics/graphics_entities_util.h"
#include "lc_client/eng_scene/entt/components.h"


class SceneApi {
public:
	SceneApi(GraphicsEntitiesUtil* pGraphicsEntitiesUtil);

	Transform& addTranfsorm(entt::id_type ent);
	void addModel(entt::id_type ent, std::string packName, std::string modelName);

private:
	GraphicsEntitiesUtil* m_pGraphicsEntitiesUtil;
	entt::registry* m_pRegistry;

	entt::entity constructEntity(entt::id_type ent);
};
