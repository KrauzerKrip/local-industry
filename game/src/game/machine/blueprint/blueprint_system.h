#pragma once

#include <entt/entt.hpp>

#include "game/machine/components.h"


class BlueprintSystem {
public:
	BlueprintSystem(entt::registry* pRegistry);

	void update(float updateInterval);

private:
	void processRequests();
	void acquireBlueprintsInInventories();
	bool isBlueprintAcquired(MachineType type);

	entt::registry* m_pRegistry = nullptr;
};