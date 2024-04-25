#pragma once

#include <entt/entt.hpp>
#include <lc_client/util/i_eng_resource.h>

#include "machine_loading_system.h"
#include "game/control/machine_control_system.h"
#include "machines/heater/heater_system.h"
#include "base_machine_system.h"
#include "machine_connector.h"
#include "graphics/machine_graphics_system.h"
#include "blueprint/blueprint_system.h"


class MachineSystem {
public:
	MachineSystem(eng::IResource* pResource, entt::registry* pRegistry, PhysicalConstants* pPhysicalConstants);

	void input(float deltaTime);
	void update(float updateInterval);
	void machineUpdate(float updateInterval);
	void frame(float deltaTime);

private:
	void completeTask(entt::entity entity);

	MachineLoadingSystem m_machineLoadingSystem;
	MachineConnector m_machineConnector;
	MachineGraphicsSystem m_machineGraphicsSystem;
	BlueprintSystem m_blueprintSystem;

	entt::registry* m_pRegistry = nullptr;

	std::vector<BaseMachineSystem*> m_machineSystems;
};
