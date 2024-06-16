#pragma once

#include "game/machine/base_machine_system.h"


class BoilerSystem : public BaseMachineSystem {
public:
	BoilerSystem(entt::registry* pRegistry, PhysicalConstants* pPhysicalConstants);

	void update(double updateInterval) override;
	void machineUpdate(double updateInterval) override;
};