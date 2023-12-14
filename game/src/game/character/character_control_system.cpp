#include "character_control_system.h"

#include <iostream>

#include <glm/ext/matrix_projection.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "lc_client/eng_physics/entt/components.h"
#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_scene/entt/components.h"
#include "components.h"


CharacterControlSystem::CharacterControlSystem(GraphicsSettings* pSettings, IInput* pInput,
	Camera* pCamera, ActionControl* pActionControl, entt::registry* pSceneRegistry, entt::registry* pMapRegistry) {
	m_pInput = pInput;
	m_pActionControl = pActionControl;
	m_pSceneRegistry = pSceneRegistry;
	m_pMapRegistry = pMapRegistry;
	m_pCamera = pCamera;

	m_windowSize = glm::vec2(1920, 1080);
	m_fov = pSettings->getFov();
	m_aspectRatio = 16.0f / 9.0f;

	m_pActionControl->addActionCallback("kb_select", [this]() { 
		onSelect(m_pInput->getMousePosition());
	});
}

void CharacterControlSystem::input() { 
	auto raycastResults = m_pSceneRegistry->view<MouseRaycast, RaycastResult>();

	for (auto&& [entity, raycastResult] : raycastResults.each()) {
		if (raycastResult.entityIntersectedWith.has_value()) {
			entt::entity intersectedEntity = raycastResult.entityIntersectedWith.value();

			if (m_pSceneRegistry->all_of<GameCharacter>(intersectedEntity)) {
				m_pSceneRegistry->emplace_or_replace<SelectedCharacter>(intersectedEntity);
				
				std::cout << "object selected" << std::endl;
			}
		}

		m_pSceneRegistry->destroy(entity);
	}
}

void CharacterControlSystem::onSelect(glm::vec2 position) { 
	glm::mat4 projection = glm::perspective(glm::radians(m_fov), m_aspectRatio, 0.1f, 1000.0f);

	glm::vec3 mouseWorld = glm::unProject(glm::vec3(position, 0.0f), m_pCamera->getViewMatrix(), projection, glm::vec4(0, 0, m_windowSize.x, m_windowSize.y));

	glm::vec3 rayDir = glm::normalize(mouseWorld - m_pCamera->getPosition());
	
	RaycastQuery raycastQuery(mouseWorld, rayDir);

	entt::entity entity = m_pSceneRegistry->create();
	
	m_pSceneRegistry->emplace<RaycastQuery>(entity, raycastQuery);
	m_pSceneRegistry->emplace<MouseRaycast>(entity, MouseRaycast());
}
