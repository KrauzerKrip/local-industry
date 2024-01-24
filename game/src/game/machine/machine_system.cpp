#include "machine_system.h"

#include "components.h"
#include "game/control/action_control.h"
#include "lc_client/eng_graphics/entt/components.h"

import character;



MachineSystem::MachineSystem(eng::IResource* pResource, entt::registry* pRegistry) : m_machineLoadingSystem(pResource, pRegistry) {
	m_pRegistry = pRegistry; }

void MachineSystem::update() { 
	m_machineLoadingSystem.update();

	auto tasks = m_pRegistry->view<Blueprint, Task>();
	
	for (auto&& [entity, task] : tasks.each()) {
		if (task.progress == TaskProgress::COMPLETED) {
			completeTask(entity);
		}
	}
}

void MachineSystem::machineUpdate() { 
	auto machinesHeatOut = m_pRegistry->view<Machine, HeatOut>();

	for (auto&& [entity, heatOut] : machinesHeatOut.each()) {
		HeatIn& heatIn = m_pRegistry->get<HeatIn>(heatOut.entity);
		heatIn.heat += heatOut.heat;
		heatOut.heat = 0;
	}
}

void MachineSystem::completeTask(entt::entity entity) {
	m_pRegistry->remove<Blueprint>(entity);
	m_pRegistry->emplace<ShaderRequest>(entity, ShaderRequest("dev", "base", "lighting"));
	m_pRegistry->remove<Transparent>(entity);
}
