#include "control_system.h"

#include "game/camera/orbital_camera_controller.h"


ControlSystem::ControlSystem(GraphicsSettings* pSettings, IInput* pInput, Camera* pCamera,
	ActionControl* pActionControl, Physics* pPhysics, entt::registry* pRegistry)
	: m_mouseRaycast(pPhysics, pSettings, pInput, pCamera, pActionControl, pRegistry),
	m_selectionSystem(pRegistry),
	  m_characterControlSystem(pRegistry),
	  m_machineControlSystem(&m_mouseRaycast, pActionControl, pRegistry), m_mouseRaycastSystem(&m_mouseRaycast, pActionControl) {

	m_pCameraController = new OrbitalCameraController(pCamera, pInput, pActionControl);

	m_mouseRaycastSystem.addObserver("kb_select", & m_selectionSystem);
	m_mouseRaycastSystem.addObserver("kb_select", &m_characterControlSystem);
	m_mouseRaycastSystem.addObserver("kb_select", & m_machineControlSystem);
	m_mouseRaycastSystem.addObserver("kb_build", &m_machineControlSystem);
}

ControlSystem::~ControlSystem() {
	delete m_pCameraController;
}

void ControlSystem::input(double deltaTime) { 
	m_pCameraController->input(deltaTime);
	m_mouseRaycastSystem.input();
	m_machineControlSystem.input();
}

void ControlSystem::update(double updateInterval) {}
