#include "model_system.h"

#include "lc_client/eng_model/entt/components.h"
#include "lc_client/eng_graphics/graphics_entities_util.h"


ModelSystem::ModelSystem(
	ModelManager* pModelManager, GraphicsEntitiesUtil* pGraphicsEntitiesUtil, entt::registry* pSceneRegistry) {
	m_pModelManager = pModelManager;
	m_pGraphicsEntitiesUtil = pGraphicsEntitiesUtil;
	m_pSceneRegistry = pSceneRegistry;
}

void ModelSystem::update() {
	auto entities = m_pSceneRegistry->view<ModelRequest>();
	
	for (auto& entity : entities) {
		ModelRequest& modelRequest = entities.get<ModelRequest>(entity);

		m_pGraphicsEntitiesUtil->setModel(entity, modelRequest.packName, modelRequest.modelName);

		m_pSceneRegistry->erase<ModelRequest>(entity);
	}


}
