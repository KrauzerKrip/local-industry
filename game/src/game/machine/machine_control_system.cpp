#include "machine_control_system.h"

MachineControlSystem::MachineControlSystem(ActionControl* pActionControl, entt::registry* pRegistry) {
	m_pActionControl = pActionControl;
	m_pRegistry = pRegistry;
}

void MachineControlSystem::input() {
	
}

void MachineControlSystem::update() {}

void MachineControlSystem::onSelect(entt::entity entity, glm::vec3 position, float distance) {}

void MachineControlSystem::onMouseMove(entt::entity entity, glm::vec3 position, float distance) {}
