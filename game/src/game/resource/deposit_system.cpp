#include "deposit_system.h"

DepositSystem::DepositSystem(entt::registry* pRegistry) : m_depositExtractionSystem(pRegistry), m_depositTaskSystem(pRegistry) { m_pRegistry = pRegistry; }

void DepositSystem::update(double updateInterval) {
	m_depositTaskSystem.update(updateInterval);
	m_depositExtractionSystem.update(updateInterval);
}