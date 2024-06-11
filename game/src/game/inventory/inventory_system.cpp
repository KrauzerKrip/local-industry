#include "inventory_system.h"


InventorySystem::InventorySystem(entt::registry* pRegistry) { m_pRegistry = pRegistry; }

void InventorySystem::update() {
	this->processUnloadings();
	this->processUnloadingTries();
	this->processLoadings();
	this->processLoadingTries();
}

void InventorySystem::processLoadings() {
	auto inventoryLoadings = m_pRegistry->view<InventoryLoad>();

	for (auto&& [entity, loading] : inventoryLoadings.each()) {
		Inventory& inventory = m_pRegistry->get<Inventory>(loading.inventory);

		if (m_pRegistry->any_of<InventoryCantLoad, InventoryLoaded>(entity)) {
			continue;
		}
		if (this->getOccupiedSpace(inventory) + loading.mass >= inventory.capacity) {
			m_pRegistry->emplace<InventoryCantLoad>(entity, loading);
			m_pRegistry->remove<InventoryLoad>(entity);
			continue;
		}

		if (inventory.items.find(loading.item) == inventory.items.end()) {
			if (this->getOccupiedSlots(inventory) < inventory.slots) {
				inventory.items.emplace(loading.item, loading.mass);
				m_pRegistry->emplace<InventoryLoaded>(entity, loading);
				m_pRegistry->remove<InventoryLoad>(entity);
			}
			else {
				m_pRegistry->emplace<InventoryCantLoad>(entity, loading);
				m_pRegistry->remove<InventoryLoad>(entity);
			}
		}
		else {
			inventory.items[loading.item] += loading.mass;
			m_pRegistry->emplace<InventoryLoaded>(entity, loading);
			m_pRegistry->remove<InventoryLoad>(entity);
		}
	}
}

void InventorySystem::processLoadingTries() { 
	auto loadingTries = m_pRegistry->view<InventoryTryLoad>();

	for (auto&& [entity, loadingTry] : loadingTries.each()) {
		Inventory& inventory = m_pRegistry->get<Inventory>(loadingTry.inventory);

		if (m_pRegistry->any_of<InventoryTriedLoad>(entity)) {
			continue;
		}

		float freeSpace = inventory.capacity - this->getOccupiedSpace(inventory);
		float shouldLoad = 0;

		if (freeSpace - loadingTry.mass >= 0) {
			shouldLoad = loadingTry.mass;
		}
		else {
			shouldLoad = freeSpace;
		}

		if (inventory.items.contains(loadingTry.item)) {
			inventory.items[loadingTry.item] += shouldLoad;
		}
		else {
			if (this->getOccupiedSlots(inventory) < inventory.slots) {
				inventory.items.emplace(loadingTry.item, shouldLoad);
			}
			else {
				shouldLoad = 0;
			}
		}

		m_pRegistry->emplace<InventoryTriedLoad>(entity, InventoryTriedLoad(loadingTry.item, shouldLoad));
		m_pRegistry->remove<InventoryTryLoad>(entity);
	}
}

void InventorySystem::processUnloadings() { 
	auto inventoryUnloadings = m_pRegistry->view<InventoryUnload>();
	
	for (auto&& [entity, unloading] : inventoryUnloadings.each()) {
		Inventory& inventory = m_pRegistry->get<Inventory>(unloading.inventory);

		if (m_pRegistry->any_of<InventoryCantUnload, InventoryUnloaded>(entity)) {
			continue;
		}
		bool isWithdrawalPossible = false;

		for (auto [item, mass] : inventory.items) {
			if (item == unloading.item) {
				if (mass >= unloading.mass) {
					isWithdrawalPossible = true;
				}
			}
		}

		if (isWithdrawalPossible) {
			inventory.items[unloading.item] -= unloading.mass;

			if (inventory.items[unloading.item] < 0.001) {
				inventory.items.erase(unloading.item);
			}

			m_pRegistry->emplace<InventoryUnloaded>(entity, unloading);
			m_pRegistry->remove<InventoryUnload>(entity);
		}	
		else {
			m_pRegistry->emplace<InventoryCantUnload>(entity, unloading);
			m_pRegistry->remove<InventoryUnload>(entity);
			continue;
		}
	}
}

void InventorySystem::processUnloadingTries() { 
	// TODO: Implement
}

unsigned int InventorySystem::getOccupiedSlots(const Inventory& inventory) { return inventory.items.size(); }

float InventorySystem::getOccupiedSpace(const Inventory& inventory) { 
	float mass = 0;
	
	for (auto [k, v] : inventory.items) {
		mass += v;
	}

	return mass;
}
