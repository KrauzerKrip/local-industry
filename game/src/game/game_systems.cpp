#include "game_systems.h"


GameSystems::GameSystems(
		entt::registry* pRegistry, eng::IResource* pResource, PhysicalConstants* pPhysicalConstants)
	: m_characterSystem(pRegistry),
	  m_machineSystem(pResource, pRegistry, pPhysicalConstants),
	  m_agricultureSystem(pRegistry),
	  m_inventorySystem(pRegistry),
	  m_tradeSystem(pRegistry),
	  m_depositSystem(pRegistry) {}

void GameSystems::input(double deltaTime) { 
	m_characterSystem.input();
	m_machineSystem.input(deltaTime);
}

void GameSystems::update(double updateInterval) { 
	m_characterSystem.update(updateInterval); 
	m_machineSystem.update(updateInterval);
	m_machineSystem.machineUpdate(updateInterval);
	m_agricultureSystem.update();
	m_inventorySystem.update();
	m_tradeSystem.update();
	m_depositSystem.update(updateInterval);
}

void GameSystems::frame(double deltaTime) { m_machineSystem.frame(deltaTime); }
