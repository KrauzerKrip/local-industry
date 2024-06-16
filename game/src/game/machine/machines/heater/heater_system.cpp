#include "heater_system.h"

#include "game/machine/components.h"
#include "components.h"

#include "game/item/classes.h"


HeaterSystem::HeaterSystem(entt::registry* pRegistry, PhysicalConstants* pPhysicalConstants) : BaseMachineSystem(pRegistry, pPhysicalConstants) {
}

void HeaterSystem::update(double updateInterval) {
    auto uninitedHeaters = m_pRegistry->view<MachineInit, Heater>();

	if (!m_pRegistry->valid(m_fuelEntity)) {
		m_fuelEntity = m_pRegistry->create();
		CombustionFuel fuel;
		fuel.burningTime = m_pPhysicalConstants->getConstant("burning_duration_wood");
		fuel.heatValue = m_pPhysicalConstants->getConstant("combustion_heat_wood");
		m_pRegistry->emplace<CombustionFuel>(m_fuelEntity, fuel);
	}

	for (auto&& [entity, heater] : uninitedHeaters.each()) {
		m_pRegistry->emplace<CombustionFuelStorage>(entity).fuel = m_fuelEntity;
		m_pRegistry->emplace<MachineMode>(entity);
		m_pRegistry->remove<MachineInit>(entity);
	}
}

void HeaterSystem::machineUpdate(double updateInterval) {
	float heaterEfficiency = m_pPhysicalConstants->getConstant("heater_efficiency");

    auto heaters = m_pRegistry->view<Heater, Machine, MachineMode, Connections, CombustionFuelStorage>();

    for (auto&& [entity, heater, mode, connections, fuelStorage] : heaters.each()) {
		if (mode.toggle) {
			if (fuelStorage.fuel.has_value() && fuelStorage.mass > 0) {
				const CombustionFuel& fuel = m_pRegistry->get<CombustionFuel>(*fuelStorage.fuel);
				float burntFuel = (1.0f / fuel.burningTime) * updateInterval;
				float heat;
				if (burntFuel < fuelStorage.mass) {
					heat = burntFuel * fuel.heatValue * heaterEfficiency;
					fuelStorage.mass -= burntFuel;
				}
				else {
					heat = fuelStorage.mass * fuel.heatValue * heaterEfficiency;
					fuelStorage.mass = 0;
				}
				connections.outputs[ConnectionResourceType::HEAT].resource = heat;
			}
		}
	}
}
