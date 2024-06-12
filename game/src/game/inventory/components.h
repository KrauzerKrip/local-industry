#pragma once

#include <unordered_map>

#include <entt/entt.hpp>



struct Inventory {
	unsigned int slots;
	float capacity; 
	std::unordered_map<entt::entity, float> items;

	Inventory(unsigned int slots, float capacity) : slots(slots), capacity(capacity) {}
};

/**
 * @brief Should be added to the entity that loads.
 */
struct InventoryLoad {
	entt::entity inventory;
	entt::entity item;
	float mass;

	InventoryLoad(entt::entity inventory, entt::entity item, float mass) : inventory(inventory), item(item), mass(mass) {}
};

/**
 * @brief Should be added to the entity that loads. After processing InventoryTriedLoad will be placed with loaded mass.
 */
struct InventoryTryLoad {
	entt::entity inventory;
	entt::entity item;
	float mass;

	InventoryTryLoad(entt::entity inventory, entt::entity item, float mass)
		: inventory(inventory),
		  item(item),
		  mass(mass) {}
};

/**
 * @brief After processing InventoryTryLoad it will be placed.
 */
struct InventoryTriedLoad {
	entt::entity inventoryEntity;
	entt::entity item;
	float massLoaded;

	InventoryTriedLoad(entt::entity inventoryEntity, entt::entity item, float massLoaded)
		: inventoryEntity(inventoryEntity),
		  item(item),
		  massLoaded(massLoaded) {}
};

struct InventoryLoaded {
	entt::entity item;
	float mass;

	InventoryLoaded(entt::entity item, float mass) : item(item), mass(mass) {}
	InventoryLoaded(const InventoryLoad& placement) : item(placement.item), mass(placement.mass) {}
};

struct InventoryCantLoad {
	entt::entity item;
	float mass;

	InventoryCantLoad(entt::entity item, float mass) : item(item), mass(mass) {}
	InventoryCantLoad(const InventoryLoad& placement) : item(placement.item), mass(placement.mass) {}
};


/**
 * @brief Should be added to the entity that withdraws
 */
struct InventoryUnload {
	entt::entity inventory;
	entt::entity item;
	float mass;

	InventoryUnload(entt::entity inventory, entt::entity item, float mass)
		: inventory(inventory),
		  item(item),
		  mass(mass) {}
};

struct InventoryUnloaded {
	entt::entity item;
	float mass;

	InventoryUnloaded(entt::entity item, float mass) : item(item), mass(mass) {}
	InventoryUnloaded(const InventoryUnload& withdrawal) : item(withdrawal.item), mass(withdrawal.mass) {}
};

struct InventoryCantUnload {
	entt::entity item;
	float mass;

	InventoryCantUnload(entt::entity item, float mass) : item(item), mass(mass) {}
	InventoryCantUnload(const InventoryUnload& withdrawal) : item(withdrawal.item), mass(withdrawal.mass) {}
};
