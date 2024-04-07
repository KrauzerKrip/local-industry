#pragma once

#include "game/machine/base_machine_system.h"


class HeaterSystem : public BaseMachineSystem {
public:
	HeaterSystem(entt::registry* pRegistry, PhysicalConstants* pPhysicalConstants);

	void update(float deltaTime) override;
	void machineUpdate(float deltaTime) override;

private:
	entt::entity m_fuelEntity;
};