#include "shader_system.h"

#include "lc_client/eng_graphics/entt/components.h"


ShaderSystem::ShaderSystem(ShaderWork* pShaderWork, entt::registry* pMapRegistry, entt::registry* pSceneRegistry) {
	m_pShaderWork = pShaderWork;
	m_pMapRegistry = pMapRegistry;
	m_pSceneRegistry = pSceneRegistry;
}

void ShaderSystem::update() { 
	auto entities = m_pSceneRegistry->view<ShaderRequest>();

	for (auto& entity : entities) {

		ShaderRequest& shaderRequest = entities.get<ShaderRequest>(entity);

		m_pShaderWork->loadShaders(entity, shaderRequest.fragmentShaderName, shaderRequest.vertexShaderName);

		m_pSceneRegistry->erase<ShaderRequest>(entity);
	}
}
