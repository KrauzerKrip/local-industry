#pragma once

#include <entt/entt.hpp>
#include <lc_client/util/i_eng_resource.h>

#include "machine_loading_system.h"
#include "game/control/machine_control_system.h"
#include "machines/heater/heater_system.h"
#include "base_machine_system.h"


class MachineSystem {
public:
	MachineSystem(eng::IResource* pResource, entt::registry* pRegistry, PhysicalConstants* pPhysicalConstants);

	void update(float deltaTime);
	void machineUpdate(float deltaTime);

private:
	void completeTask(entt::entity entity);

	MachineLoadingSystem m_machineLoadingSystem;

	entt::registry* m_pRegistry = nullptr;

	std::vector<BaseMachineSystem*> m_machineSystems;
};
