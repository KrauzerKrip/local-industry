#include "inventory_system_tests.h"

void InventorySystemTests::SetUp() { m_pRegistry = new entt::registry(); }

void InventorySystemTests::TearDown() { delete m_pRegistry; }
