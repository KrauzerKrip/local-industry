#include "machine_system.h"

#include "components.h"
#include "game/control/action_control.h"
#include "game/control/components.h"
#include "lc_client/eng_graphics/entt/components.h"
#include "physics/physical_constants.h"
#include "machines/heater/heater_system.h"
#include "machines/boiler/boiler_system.h"
#include "game/character/components.h"

#include "game/character/task_queue.h"



MachineSystem::MachineSystem(eng::IResource* pResource, entt::registry* pRegistry, PhysicalConstants* pPhysicalConstants) : m_machineLoadingSystem(pResource, pRegistry), m_machineConnector(pRegistry), m_machineGraphicsSystem(pRegistry), m_blueprintSystem(pRegistry) {
	m_pRegistry = pRegistry;

	m_machineSystems = {
		new HeaterSystem(pRegistry, pPhysicalConstants),
	    new BoilerSystem(pRegistry, pPhysicalConstants)
	};
}

void MachineSystem::input(float deltaTime) {
}

void MachineSystem::update(float updateInterval) {
	m_blueprintSystem.update(updateInterval);
	m_machineLoadingSystem.update();

	auto tasks = m_pRegistry->view<Blueprint, Task>();
	
	for (auto&& [entity, task] : tasks.each()) {
		if (task.progress == TaskProgress::COMPLETED) {
			completeTask(entity);
		}
	}

    for (BaseMachineSystem* pMachineSystem : m_machineSystems) {
		pMachineSystem->update(updateInterval);
	}
}
  
void MachineSystem::machineUpdate(float updateInterval) { 
    for (BaseMachineSystem* pMachineSystem : m_machineSystems) {
		pMachineSystem->machineUpdate(updateInterval);
	}

	auto machines = m_pRegistry->view<Machine, Connections>();
	for (auto&& [entity, connections] : machines.each()) {
		for (auto& [resourceType, connection] : connections.outputs) {
			if (connection.resource > 0 && connection.entity.has_value()) {
				Connection& inputConnection = m_pRegistry->get<Connections>(connection.entity.value()).inputs.at(resourceType);
				inputConnection.resource += connection.resource;
				connection.resource = 0;
			}
		}
	}
}

void MachineSystem::frame(float deltaTime) { m_machineGraphicsSystem.frame(deltaTime); }

void MachineSystem::completeTask(entt::entity entity) {
	m_pRegistry->emplace<Machine>(entity);
	m_pRegistry->emplace<Built>(entity);
	m_pRegistry->remove<Blueprint>(entity);
	m_pRegistry->emplace<ShaderRequest>(entity, ShaderRequest("dev", "base", "lighting"));
	m_pRegistry->remove<Transparent>(entity);

	if (m_pRegistry->all_of<Selected>(entity)) {
		m_pRegistry->remove<Selected>(entity);
	}
	if (m_pRegistry->all_of<Outline>(entity)) {
		m_pRegistry->remove<Outline>(entity);
	}

	if (m_pRegistry->all_of<ConnectionRequest>(entity)) {
	    ConnectionRequest& request = m_pRegistry->get<ConnectionRequest>(entity);
		if (request.resourceType != ConnectionResourceType::NONE) {
			m_machineConnector.connect(request.resourceType, request.type, entity, request.entity);
		}

		m_pRegistry->remove<ConnectionRequest>(entity);
	}
}
