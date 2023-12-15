#include "control_system.h"

ControlSystem::ControlSystem(GraphicsSettings* pSettings, IInput* pInput, Camera* pCamera,
	ActionControl* pActionControl, entt::registry* pSceneRegistry, entt::registry* pMapRegistry) {
	m_pMouseRaycastSystem = new MouseRaycastSystem(pSettings, pInput, pCamera, pActionControl, pSceneRegistry, pMapRegistry);
	m_pSelectionSystem = new SelectionSystem(pSceneRegistry, pMapRegistry);

	m_pMouseRaycastSystem->addObserver(m_pSelectionSystem);
}

ControlSystem::~ControlSystem() {
	delete m_pMouseRaycastSystem;
	delete m_pSelectionSystem;
}

void ControlSystem::input() { m_pMouseRaycastSystem->input(); }

void ControlSystem::update() {}
