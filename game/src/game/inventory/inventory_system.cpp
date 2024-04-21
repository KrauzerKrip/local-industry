#include "inventory_system.h"


InventorySystem::InventorySystem(entt::registry* pRegistry) { m_pRegistry = pRegistry; }

void InventorySystem::update() { 
	auto inventoryPlacements = m_pRegistry->view<InventoryPlacement>();

	for (auto&& [entity, placement] : inventoryPlacements.each()) {
		Inventory& inventory = m_pRegistry->get<Inventory>(placement.inventory);

		if (m_pRegistry->any_of<InventoryCantPlace, InventoryPlaced>(entity)) {
			continue;
		}
		if (this->getOccupiedSpace(inventory) >= inventory.capacity) {
			m_pRegistry->emplace<InventoryCantPlace>(entity, placement);
			m_pRegistry->remove<InventoryPlacement>(entity);
			continue;
		}

		if (inventory.items.find(placement.item) == inventory.items.end()) {
			if (this->getOccupiedSlots(inventory) < inventory.slots) {
				inventory.items.emplace(placement.item, placement.mass);
				m_pRegistry->emplace<InventoryPlaced>(entity, placement);
				m_pRegistry->remove<InventoryPlacement>(entity);
			}
			else {
				m_pRegistry->emplace<InventoryCantPlace>(entity, placement);
				m_pRegistry->remove<InventoryPlacement>(entity);
			}
		}
		else {
			inventory.items[placement.item] += placement.mass;
			m_pRegistry->emplace<InventoryPlaced>(entity, placement);
			m_pRegistry->remove<InventoryPlacement>(entity);
		}
	}

}

unsigned int InventorySystem::getOccupiedSlots(const Inventory& inventory) { return inventory.items.size(); }

float InventorySystem::getOccupiedSpace(const Inventory& inventory) { 
	float mass = 0;
	
	for (auto [k, v] : inventory.items) {
		mass += v;
	}

	return mass;
}
