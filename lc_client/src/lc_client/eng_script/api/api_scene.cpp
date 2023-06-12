#include "api_scene.h"
#include "api_scene.h"

#include "ldk_client/local_engine/scene_controlling.h"
#include <lc_client/eng_model/entt/components.h>

#include "lc_client/eng_script/script_system.h"


SceneApi::SceneApi(entt::registry* pSceneRegistry) : m_registryHelper(pSceneRegistry) {
	m_pRegistry = pSceneRegistry; }

RegistryHelper& SceneApi::getRegistry() { return m_registryHelper; }

TransformHelper SceneApi::addTranfsorm(entt::id_type ent) { 
	auto entity = constructEntity(ent);
	Transform& transform = m_pRegistry->emplace_or_replace<Transform>(entity);

	return TransformHelper(entity, m_pRegistry);
}

PointLight& SceneApi::addPointLight(entt::id_type ent) { 
	auto entity = constructEntity(ent);
	return m_pRegistry->emplace_or_replace<PointLight>(entity);
}

void SceneApi::requestModel(entt::id_type ent, std::string packName, std::string modelName) {
	auto entity = constructEntity(ent);
	m_pRegistry->emplace_or_replace<ModelRequest>(entity, packName, modelName);
}



entt::entity SceneApi::constructEntity(entt::id_type ent) { 
	auto version_type = entt::entt_traits<entt::entity>::version_type();
	return entt::entt_traits<entt::entity>::construct(ent, version_type);
}
