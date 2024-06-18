#include "game_systems.h"


GameSystems::GameSystems(entt::registry* pRegistry, eng::IResource* pResource, PhysicalConstants* pPhysicalConstants,
	IConsole* pConsole, Parameters* pParameters)
	: m_characterSystem(pRegistry),
	  m_machineSystem(pResource, pRegistry, pPhysicalConstants, pParameters),
	  m_agricultureSystem(pRegistry),
	  m_inventorySystem(pRegistry),
	  m_tradeSystem(pRegistry),
	  m_depositSystem(pRegistry, pConsole) {}

void GameSystems::input(double deltaTime) { 
	m_characterSystem.input();
	m_machineSystem.input(deltaTime);
}

void GameSystems::update(double updateInterval) { 
	m_characterSystem.update(updateInterval); 
	m_machineSystem.update(updateInterval);
	m_agricultureSystem.update(updateInterval);
	m_tradeSystem.update();
	m_depositSystem.update(updateInterval);
	m_inventorySystem.update();
}

void GameSystems::machineUpdate(double updateInterval) { 
	m_agricultureSystem.machineUpdate(updateInterval);
	m_machineSystem.machineUpdate(updateInterval);
}

void GameSystems::frame(double deltaTime) { m_machineSystem.frame(deltaTime); }
