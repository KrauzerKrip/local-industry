#include "registry_helper.h"
#include "registry_helper.h"
#include "lc_client/eng_model/entt/components.h"
#include "lc_client/eng_script/script_system.h"


RegistryHelper::RegistryHelper(entt::registry* pRegistry) { m_pRegistry = pRegistry; }

void RegistryHelper::addTransform(entt::id_type ent) {
	auto entity = constructEntity(ent);
	Transform& transform = m_pRegistry->emplace_or_replace<Transform>(entity);
}

Transform& RegistryHelper::getTransform(entt::id_type ent) { return m_pRegistry->get<Transform>(constructEntity(ent)); }

PointLight& RegistryHelper::addPointLight(entt::id_type ent) {
	auto entity = constructEntity(ent);
	return m_pRegistry->emplace_or_replace<PointLight>(entity);
}

void RegistryHelper::requestModel(entt::id_type ent, std::string packName, std::string modelName) {
	auto entity = constructEntity(ent);
	m_pRegistry->emplace_or_replace<ModelRequest>(entity, packName, modelName);
}


entt::entity RegistryHelper::constructEntity(entt::id_type ent) {
	auto version_type = entt::entt_traits<entt::entity>::version_type();

	return entt::entt_traits<entt::entity>::construct(ent, version_type);
}
