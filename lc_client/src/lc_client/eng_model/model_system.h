#pragma once

#include <entt/entt.hpp>

#include "model_manager.h"


class ModelSystem {
public:
	ModelSystem(ModelManager* pModelManager, GraphicsEntitiesUtil* pGraphicsEntitiesUtil, entt::registry* pSceneRegistry);

	void update();

private:
	ModelManager* m_pModelManager = nullptr;
	GraphicsEntitiesUtil* m_pGraphicsEntitiesUtil = nullptr;
	entt::registry* m_pSceneRegistry = nullptr;
};
