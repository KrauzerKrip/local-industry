#include "api_scene.h"

#include "ldk_client/local_engine/scene_controlling.h"
#include <lc_client/eng_model/entt/components.h>

#include "lc_client/eng_script/script_system.h"


SceneApi::SceneApi() {
	m_pRegistry = &SceneControlling::getScene()->getSceneRegistry();
}

TransformHelper SceneApi::addTranfsorm(entt::id_type ent) { 
	auto entity = constructEntity(ent);
	Transform& transform = m_pRegistry->emplace_or_replace<Transform>(entity);

	std::string id = ScriptSystem::m_currentId;

	long iPtr = (long)&transform;

	std::string str = std::to_string(iPtr);

	std::string id_ = m_pRegistry->get<Properties>(entity).id;

	Tier0::getIConsole()->devMessage("ADD_TRANSFORM Transform ptr: " + id + " "+ id_ + " " + str);

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
