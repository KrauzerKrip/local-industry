#pragma once

#include <entt/entt.hpp>
#include <lc_client/util/i_eng_resource.h>

#include "machine_loading_system.h"


class MachineSystem {
public:
	MachineSystem(eng::IResource* pResource, entt::registry* pRegistry);

	void update();
	void machineUpdate();

private:
	MachineLoadingSystem m_machineLoadingSystem;

	entt::registry* m_pRegistry = nullptr;
};
