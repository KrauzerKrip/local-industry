#include "shader_system.h"

#include "lc_client/eng_graphics/entt/components.h"


ShaderSystem::ShaderSystem(ShaderWork* pShaderWork, entt::registry* pRegistry) {
	m_pShaderWork = pShaderWork;
	m_pRegistry = pRegistry;
}

void ShaderSystem::update() { 
	auto sceneEntities = m_pRegistry->view<ShaderRequest>();

	for (auto& entity : sceneEntities) {

		ShaderRequest& shaderRequest = sceneEntities.get<ShaderRequest>(entity);

		m_pShaderWork->loadShaders(
			m_pRegistry, entity, shaderRequest.vertexShaderName, shaderRequest.fragmentShaderName);

		m_pRegistry->erase<ShaderRequest>(entity);
	}
}
