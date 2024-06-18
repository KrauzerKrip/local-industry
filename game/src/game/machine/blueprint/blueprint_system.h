#pragma once

#include <entt/entt.hpp>

#include "game/machine/components.h"
#include "lc_client/tier0/conpar/parameters.h"

class BlueprintSystem {
public:
	BlueprintSystem(entt::registry* pRegistry, Parameters* pParameters);

	void update(float updateInterval);

private:
	void processRequests();
	void acquireBlueprintsInInventories();
	bool isBlueprintAcquired(MachineType type);

	entt::registry* m_pRegistry = nullptr;
	Parameters* m_pParameters = nullptr;
};