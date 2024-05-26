#include "deposit_task_system.h"

#include "components.h"
#include "game/character/components.h"


DepositTaskSystem::DepositTaskSystem(entt::registry* pRegistry) { m_pRegistry = pRegistry; }

void DepositTaskSystem::update(double updateInterval) { 
	//auto depositTasks = m_pRegistry->view<ResourceDeposit, Task>
}
