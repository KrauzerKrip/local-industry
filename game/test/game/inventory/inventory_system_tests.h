#pragma once

#include <gtest/gtest.h>
#include <entt/entt.hpp>

#include "game/inventory/inventory_system.h"

class InventorySystemTests : public testing::Test {
protected:
	void SetUp();
	void TearDown();

	entt::registry* m_pRegistry = nullptr;
};

TEST_F(InventorySystemTests, inventory_system_tryload_test) { 
	InventorySystem inventorySystem(m_pRegistry);

	auto itemEnt = m_pRegistry->create();
	auto otherItemEnt = m_pRegistry->create();

	auto inventoryEnt = m_pRegistry->create();
	Inventory& inventory = m_pRegistry->emplace<Inventory>(inventoryEnt, Inventory(1, 5));

	// should not load
	auto loaderEnt = m_pRegistry->create();
	inventory.items[otherItemEnt] = 1;
	m_pRegistry->emplace<InventoryTryLoad>(loaderEnt, InventoryTryLoad(inventoryEnt, itemEnt, 2.5));
	inventorySystem.update();
	EXPECT_EQ(inventory.items[itemEnt], 0);
	EXPECT_TRUE(m_pRegistry->all_of<InventoryTriedLoad>(loaderEnt));
	float massLoaded = m_pRegistry->get<InventoryTriedLoad>(loaderEnt).massLoaded;
	EXPECT_EQ(massLoaded, 0);

	m_pRegistry->remove<InventoryTriedLoad>(loaderEnt);
	inventory.items.clear();

	// should load 5 
	m_pRegistry->emplace<InventoryTryLoad>(loaderEnt, InventoryTryLoad(inventoryEnt, itemEnt, 7));
	inventorySystem.update();
	EXPECT_EQ(inventory.items[itemEnt], 5);
	EXPECT_TRUE(m_pRegistry->all_of<InventoryTriedLoad>(loaderEnt));
	massLoaded = m_pRegistry->get<InventoryTriedLoad>(loaderEnt).massLoaded;
	EXPECT_EQ(massLoaded, 5);

	m_pRegistry->remove<InventoryTriedLoad>(loaderEnt);
	inventory.items.clear();

	// should load the entire resource
	m_pRegistry->emplace<InventoryTryLoad>(loaderEnt, InventoryTryLoad(inventoryEnt, itemEnt, 2.5));
	inventorySystem.update();
	EXPECT_EQ(inventory.items[itemEnt], 2.5);
	EXPECT_TRUE(m_pRegistry->all_of<InventoryTriedLoad>(loaderEnt));
	massLoaded = m_pRegistry->get<InventoryTriedLoad>(loaderEnt).massLoaded;
	EXPECT_EQ(massLoaded, 2.5);
};
