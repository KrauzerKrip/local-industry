#include "control_system.h"

ControlSystem::ControlSystem(GraphicsSettings* pSettings, IInput* pInput, Camera* pCamera,
	ActionControl* pActionControl, entt::registry* pRegistry) {
	m_pMouseRaycastSystem = new MouseRaycastSystem(pSettings, pInput, pCamera, pActionControl, pRegistry);
	m_pSelectionSystem = new SelectionSystem(pRegistry);
	m_pCharacterControlSystem = new CharacterControlSystem(pRegistry);

	m_pMouseRaycastSystem->addObserver(m_pSelectionSystem);
	m_pMouseRaycastSystem->addObserver(m_pCharacterControlSystem);
}

ControlSystem::~ControlSystem() {
	delete m_pMouseRaycastSystem;
	delete m_pSelectionSystem;
	delete m_pCharacterControlSystem;
}

void ControlSystem::input() { m_pMouseRaycastSystem->input(); }

void ControlSystem::update() {}
