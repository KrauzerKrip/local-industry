#include "inventory_system.h"


InventorySystem::InventorySystem(entt::registry* pRegistry) { m_pRegistry = pRegistry; }

void InventorySystem::update() {
	this->processWithdrawals();
	this->processPlacements();
}

void InventorySystem::processPlacements() {
	auto inventoryPlacements = m_pRegistry->view<InventoryLoad>();

	for (auto&& [entity, placement] : inventoryPlacements.each()) {
		Inventory& inventory = m_pRegistry->get<Inventory>(placement.inventory);

		if (m_pRegistry->any_of<InventoryCantLoad, InventoryLoaded>(entity)) {
			continue;
		}
		if (this->getOccupiedSpace(inventory) >= inventory.capacity) {
			m_pRegistry->emplace<InventoryCantLoad>(entity, placement);
			m_pRegistry->remove<InventoryLoad>(entity);
			continue;
		}

		if (inventory.items.find(placement.item) == inventory.items.end()) {
			if (this->getOccupiedSlots(inventory) < inventory.slots) {
				inventory.items.emplace(placement.item, placement.mass);
				m_pRegistry->emplace<InventoryLoaded>(entity, placement);
				m_pRegistry->remove<InventoryLoad>(entity);
			}
			else {
				m_pRegistry->emplace<InventoryCantLoad>(entity, placement);
				m_pRegistry->remove<InventoryLoad>(entity);
			}
		}
		else {
			inventory.items[placement.item] += placement.mass;
			m_pRegistry->emplace<InventoryLoaded>(entity, placement);
			m_pRegistry->remove<InventoryLoad>(entity);
		}
	}
}

void InventorySystem::processWithdrawals() { 
	auto inventoryWithdrawals = m_pRegistry->view<InventoryUnload>();
	
	for (auto&& [entity, withdrawal] : inventoryWithdrawals.each()) {
		Inventory& inventory = m_pRegistry->get<Inventory>(withdrawal.inventory);

		if (m_pRegistry->any_of<InventoryCantUnload, InventoryUnloaded>(entity)) {
			continue;
		}
		bool isWithdrawalPossible = false;

		for (auto [item, mass] : inventory.items) {
			if (item == withdrawal.item) {
				if (mass >= withdrawal.mass) {
					isWithdrawalPossible = true;
				}
			}
		}

		if (isWithdrawalPossible) {
			inventory.items[withdrawal.item] -= withdrawal.mass;

			if (inventory.items[withdrawal.item] < 0.001) {
				inventory.items.erase(withdrawal.item);
			}

			m_pRegistry->emplace<InventoryUnloaded>(entity, withdrawal);
			m_pRegistry->remove<InventoryUnload>(entity);
		}	
		else {
			m_pRegistry->emplace<InventoryCantUnload>(entity, withdrawal);
			m_pRegistry->remove<InventoryUnload>(entity);
			continue;
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
