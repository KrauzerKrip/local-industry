#include "machine_system.h"

#include "components.h"
#include "game/control/action_control.h"
#include "lc_client/eng_graphics/entt/components.h"
#include "physics/physical_constants.h"
#include "machines/heater/heater_system.h"
#include "machines/boiler/boiler_system.h"


import character;



MachineSystem::MachineSystem(eng::IResource* pResource, entt::registry* pRegistry, PhysicalConstants* pPhysicalConstants) : m_machineLoadingSystem(pResource, pRegistry) {
	m_pRegistry = pRegistry;

	m_machineSystems = {
		new HeaterSystem(pRegistry, pPhysicalConstants),
	    new BoilerSystem(pRegistry, pPhysicalConstants)
	};
}

void MachineSystem::update(float deltaTime) { 
	m_machineLoadingSystem.update();

	auto tasks = m_pRegistry->view<Blueprint, Task>();
	
	for (auto&& [entity, task] : tasks.each()) {
		if (task.progress == TaskProgress::COMPLETED) {
			completeTask(entity);
		}
	}

    for (BaseMachineSystem* pMachineSystem : m_machineSystems) {
		pMachineSystem->update(deltaTime);
	}
}

void MachineSystem::machineUpdate(float deltaTime) { 
	auto machinesHeatOut = m_pRegistry->view<Machine, HeatOut>();

    for (BaseMachineSystem* pMachineSystem : m_machineSystems) {
		pMachineSystem->machineUpdate(deltaTime);
	}

	for (auto&& [entity, heatOut] : machinesHeatOut.each()) {
		if (heatOut.entity) {
			HeatIn& heatIn = m_pRegistry->get<HeatIn>(heatOut.entity.value());
			heatIn.heat += heatOut.heat;
			heatOut.heat = 0;
		}
	}
}

void MachineSystem::completeTask(entt::entity entity) {
	m_pRegistry->remove<Blueprint>(entity);
	m_pRegistry->emplace<ShaderRequest>(entity, ShaderRequest("dev", "base", "lighting"));
	m_pRegistry->remove<Transparent>(entity);
}
