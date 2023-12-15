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

	//m_pActionControl->addActionCallback("kb_unselect", [this]() { onUnselect(m_pInput->getMousePosition()); });
}

void CharacterControlSystem::input() { 
	
}

void CharacterControlSystem::onSelect(glm::vec2 position) { 
}

void CharacterControlSystem::onUnselect(glm::vec2 position) {
}
