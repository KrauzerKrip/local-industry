#pragma once

#include <entt/entt.hpp>

#include "game/machine/machine_type.h"


class MachineBlueprintCreator {
public:
	MachineBlueprintCreator(entt::registry* pRegistry);

	void createMachineBlueprint(MachineType type, std::string typeString);

private:

	entt::registry* m_pRegistry = nullptr;
};
