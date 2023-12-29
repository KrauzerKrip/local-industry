#pragma once

#include <entt/entt.hpp>

#include "lc_client/util/i_eng_resource.h"

#include "machine_loader.h"
#include "machine_type.h"


class MachineLoadingSystem {
public:
	MachineLoadingSystem(eng::IResource* pResource, entt::registry* pRegistry);

	void update();

private:
	void addMachineComponent(entt::entity entity, MachineType type);

	MachineLoader m_machineLoader;

	entt::registry* m_pRegistry = nullptr;
};