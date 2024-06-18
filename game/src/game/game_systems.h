#pragma once

#include <entt/entt.hpp>

#include "lc_client/util/i_eng_resource.h"
#include "machine/physics/physical_constants.h"

#include "machine/machine_system.h"
#include "agriculture/agriculture_system.h"
#include "inventory/inventory_system.h"
#include "economy/trade_system.h"
#include "resource/deposit_system.h"
#include "character/character_system.h"
#include "lc_client/tier0/conpar/parameters.h"


class GameSystems {
public:
	GameSystems(entt::registry* pRegistry, eng::IResource* pResource, PhysicalConstants* pPhysicalConstants,
		IConsole* pConsole, Parameters* pParameters);

	void input(double deltaTime);
	void update(double updateInterval);
	void machineUpdate(double updateInterval);
	void frame(double deltaTime);

private:
	CharacterSystem m_characterSystem;
	MachineSystem m_machineSystem;
	AgricultureSystem m_agricultureSystem;
	InventorySystem m_inventorySystem;
	TradeSystem m_tradeSystem;
	DepositSystem m_depositSystem;
};