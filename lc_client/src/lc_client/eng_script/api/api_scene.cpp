#include "api_scene.h"

#include "ldk_client/local_engine/scene_controlling.h"


SceneApi::SceneApi(GraphicsEntitiesUtil* pGraphicsEntitiesUtil) {
	m_pGraphicsEntitiesUtil = pGraphicsEntitiesUtil;
	m_pRegistry = &SceneControlling::getScene()->getSceneRegistry();
}

Transform& SceneApi::addTranfsorm(entt::id_type ent) { 
	auto entity = constructEntity(ent);
	return m_pRegistry->emplace<Transform>(entity);
}

void SceneApi::addModel(entt::id_type ent, std::string packName, std::string modelName) {
	auto entity = constructEntity(ent);
	m_pGraphicsEntitiesUtil->setModel(entity, packName, modelName);
}



entt::entity SceneApi::constructEntity(entt::id_type ent) { 
	auto version_type = entt::entt_traits<entt::entity>::version_type();

	return entt::entt_traits<entt::entity>::construct(ent, version_type);
}
