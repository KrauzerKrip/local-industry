#include "machine_loading_system.h"

#include "components.h"
#include "lc_client/eng_scene/entt/components.h"
#include "machines/heater/components.h"
#include "machines/boiler/components.h"


MachineLoadingSystem::MachineLoadingSystem(eng::IResource* pResource, entt::registry* pRegistry) :m_machineLoader(pResource, pRegistry) {
	m_pRegistry = pRegistry;
}

void MachineLoadingSystem::update() { 
	auto machineRequests = m_pRegistry->view<MachineRequest>();

	for (auto&& [entity, request] : machineRequests.each()) {
		m_machineLoader.loadMachine(entity, request.typeString);
		addMachineComponent(entity, request.type);
		m_pRegistry->emplace<Properties>(entity, Properties());
		m_pRegistry->remove<MachineRequest>(entity);
	}
}

void MachineLoadingSystem::addMachineComponent(entt::entity entity, MachineType type) {
	switch (type) {
	case MachineType::HEATER:
		m_pRegistry->emplace<Heater>(entity);
		break;
	case MachineType::BOILER:
		m_pRegistry->emplace<Boiler>(entity);
		break;
	default:
		break;
	}
	m_pRegistry->emplace<MachineInit>(entity);
}
