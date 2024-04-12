#include "shader_system.h"

#include "lc_client/eng_graphics/entt/components.h"


ShaderSystem::ShaderSystem(ShaderLoader* pShaderWork, entt::registry* pRegistry) {
	m_pShaderWork = pShaderWork;
	m_pRegistry = pRegistry;
}

void ShaderSystem::update() { 
	auto sceneEntities = m_pRegistry->view<ShaderRequest>();

	for (auto& entity : sceneEntities) {
		ShaderRequest& shaderRequest = sceneEntities.get<ShaderRequest>(entity);

		m_pShaderWork->loadShaders(
			m_pRegistry, entity, shaderRequest.vertexShaderName, shaderRequest.fragmentShaderName);

		m_pRegistry->emplace<ShaderData>(entity, ShaderData(shaderRequest.packName, shaderRequest.vertexShaderName, shaderRequest.fragmentShaderName));

		m_pRegistry->erase<ShaderRequest>(entity);
	}

	auto reloadRequests = m_pRegistry->view<ShaderReloadRequest, ShaderData>();

	for (auto&& [entity, data] : reloadRequests.each()) {
		m_pShaderWork->loadShaders(m_pRegistry, entity, data.vertexShaderName, data.fragmentShaderName);
		m_pRegistry->remove<ShaderReloadRequest>(entity);
	}
}
