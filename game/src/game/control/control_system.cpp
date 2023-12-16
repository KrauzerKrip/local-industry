#include "control_system.h"

ControlSystem::ControlSystem(GraphicsSettings* pSettings, IInput* pInput, Camera* pCamera,
	ActionControl* pActionControl, entt::registry* pRegistry) {
	m_pMouseRaycastSystem = new MouseRaycastSystem(pSettings, pInput, pCamera, pActionControl, pRegistry);
	m_pSelectionSystem = new SelectionSystem(pRegistry);

	m_pMouseRaycastSystem->addObserver(m_pSelectionSystem);
}

ControlSystem::~ControlSystem() {
	delete m_pMouseRaycastSystem;
	delete m_pSelectionSystem;
}

void ControlSystem::input() { m_pMouseRaycastSystem->input(); }

void ControlSystem::update() {}
