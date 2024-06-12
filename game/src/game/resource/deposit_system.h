#pragma once

#include <entt/entt.hpp>
#include "deposit_task_system.h"
#include "deposit_extraction_system.h"


class DepositSystem {
public:
	DepositSystem(entt::registry* pRegistry, IConsole* pConsole);

	void update(double updateInterval);

private:
	entt::registry* m_pRegistry = nullptr;

	DepositExtractionSystem m_depositExtractionSystem;
	DepositTaskSystem m_depositTaskSystem;
};