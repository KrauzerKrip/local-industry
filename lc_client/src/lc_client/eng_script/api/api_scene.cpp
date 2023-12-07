#include "api_scene.h"
#include "api_scene.h"

#include "ldk_client/local_engine/scene_controlling.h"
#include <lc_client/eng_model/entt/components.h>

#include "lc_client/eng_script/script_system.h"


SceneApi::SceneApi(entt::registry* pSceneRegistry) : m_registryHelper(pSceneRegistry) {
	m_pRegistry = pSceneRegistry; }

RegistryHelper& SceneApi::getRegistry() { return m_registryHelper; }

entt::entity SceneApi::constructEntity(entt::id_type ent) { 
	auto version_type = entt::entt_traits<entt::entity>::version_type();
	return entt::entt_traits<entt::entity>::construct(ent, version_type);
}
