#include "machine_system.h"

#include "components.h"


MachineSystem::MachineSystem(eng::IResource* pResource, entt::registry* pRegistry) : m_machineLoadingSystem(pResource, pRegistry) {
	m_pRegistry = pRegistry; }

void MachineSystem::update() { 
	m_machineLoadingSystem.update();
}

void MachineSystem::machineUpdate() { 
	auto machinesHeatOut = m_pRegistry->view<Machine, HeatOut>();

	for (auto&& [entity, heatOut] : machinesHeatOut.each()) {
		HeatIn& heatIn = m_pRegistry->get<HeatIn>(heatOut.entity);
		heatIn.heat += heatOut.heat;
		heatOut.heat = 0;
	}
}
