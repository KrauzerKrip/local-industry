#include "boiler_system.h"

#include "game/machine/components.h"
#include "components.h"


BoilerSystem::BoilerSystem(entt::registry* pRegistry, PhysicalConstants* pPhysicalConstants) :
	BaseMachineSystem(pRegistry, pPhysicalConstants) {}

void BoilerSystem::update(float deltaTime) {
    auto uninitedBoilers = m_pRegistry->view<MachineInit, Boiler>();

	for (auto&& [entity, boiler] : uninitedBoilers.each()) {
		//m_pRegistry->emplace<Attachment>(entity);
		m_pRegistry->remove<MachineInit>(entity);
	}
}

void BoilerSystem::machineUpdate(float deltaTime) {}
