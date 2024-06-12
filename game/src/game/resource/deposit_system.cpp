#include "deposit_system.h"

DepositSystem::DepositSystem(entt::registry* pRegistry, IConsole* pConsole)
	: m_depositExtractionSystem(pRegistry),
	  m_depositTaskSystem(pRegistry, pConsole) {
	m_pRegistry = pRegistry;
}

void DepositSystem::update(double updateInterval) {
	m_depositTaskSystem.update(updateInterval);
	m_depositExtractionSystem.update(updateInterval);
}