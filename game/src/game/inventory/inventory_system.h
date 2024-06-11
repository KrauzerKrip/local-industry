#pragma once

#include <entt/entt.hpp>

#include "components.h"


class InventorySystem {
public:
	InventorySystem(entt::registry* pRegistry);

	void update();

private:
	void processLoadings();
	void processLoadingTries();
	void processUnloadings();
	void processUnloadingTries();

	unsigned int getOccupiedSlots(const Inventory& inventory);
	float getOccupiedSpace(const Inventory& inventory);

	entt::registry* m_pRegistry = nullptr;
};