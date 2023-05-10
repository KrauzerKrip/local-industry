#include "api_scene.h"

#include "ldk_client/local_engine/scene_controlling.h"
#include <lc_client/eng_model/entt/components.h>


SceneApi::SceneApi() {
	m_pRegistry = &SceneControlling::getScene()->getSceneRegistry();
}

TransformHelper SceneApi::addTranfsorm(entt::id_type ent) { 

	auto entity = constructEntity(ent);
	return TransformHelper(&m_pRegistry->emplace_or_replace<Transform>(entity));
}

void SceneApi::requestModel(entt::id_type ent, std::string packName, std::string modelName) {
	auto entity = constructEntity(ent);
	m_pRegistry->emplace_or_replace<ModelRequest>(entity, packName, modelName);
}



entt::entity SceneApi::constructEntity(entt::id_type ent) { 
	auto version_type = entt::entt_traits<entt::entity>::version_type();

	return entt::entt_traits<entt::entity>::construct(ent, version_type);
}
