#pragma once

#include <unordered_map>

#include <entt/entt.hpp>


enum class InventoryResponseStatus {
	SUCCESS,
	FAIL
};


struct Inventory {
	unsigned int slots;
	float capacity;
	std::unordered_map<entt::entity, float> items;

	Inventory(unsigned int slots, float capacity) : slots(slots), capacity(capacity) {}
};

struct InventoryPlacement {
	entt::entity inventory;
	entt::entity item;
	float mass;

	InventoryPlacement(entt::entity inventory, entt::entity item, float mass) : inventory(inventory), item(item), mass(mass) {}
};

struct InventoryPlaced {
	entt::entity item;
	float mass;

	InventoryPlaced(entt::entity item, float mass) : item(item), mass(mass) {}
	InventoryPlaced(const InventoryPlacement& placement) : item(placement.item), mass(placement.mass) {}
};

struct InventoryCantPlace {
	entt::entity item;
	float mass;

	InventoryCantPlace(entt::entity item, float mass) : item(item), mass(mass) {}
	InventoryCantPlace(const InventoryPlacement& placement) : item(placement.item), mass(placement.mass) {}
};
