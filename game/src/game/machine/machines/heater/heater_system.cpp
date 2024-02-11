#include "heater_system.h"

#include "game/machine/components.h"
#include "components.h"

#include "game/item/classes.h"


HeaterSystem::HeaterSystem(entt::registry* pRegistry, PhysicalConstants* pPhysicalConstants) : BaseMachineSystem(pRegistry, pPhysicalConstants) {}

void HeaterSystem::update(float deltaTime) {
    auto uninitedHeaters = m_pRegistry->view<MachineInit, Heater>();

	for (auto&& [entity, heater] : uninitedHeaters.each()) {
		m_pRegistry->emplace<CombustionFuelStorage>(entity);
		m_pRegistry->remove<MachineInit>(entity); 
	}
}

void HeaterSystem::machineUpdate(float deltaTime) {
	float heaterEfficiency = m_pPhysicalConstants->getConstant("heater_efficiency");

    auto heaters = m_pRegistry->view<Heater, Machine, HeatOut, CombustionFuelStorage>();

    for (auto&& [entity, heater, heatOut, fuelStorage] : heaters.each()) {
		if (heater.isWorking) {
			if (fuelStorage.fuel.has_value() && fuelStorage.mass > 0) {
				const CombustionFuel& fuel = m_pRegistry->get<CombustionFuel>(*fuelStorage.fuel);
				float burntFuel = (1.0f / fuel.burningTime) * deltaTime;
				float heat;
				if (burntFuel > fuelStorage.mass) {
					heat = burntFuel * fuel.heatValue * heaterEfficiency;
					fuelStorage.mass -= burntFuel;
				}
				else {
					heat = fuelStorage.mass * fuel.heatValue * heaterEfficiency;
					fuelStorage.mass = 0;
				}
				heatOut.heat = heat;
			}
		}
	}
}
