#include "deposit_task_system.h"

#include "components.h"
#include "game/character/components.h"
#include "game/inventory/components.h"


DepositTaskSystem::DepositTaskSystem(entt::registry* pRegistry) { m_pRegistry = pRegistry; }

void DepositTaskSystem::update(double updateInterval) { 
	auto depositTasks = m_pRegistry->view<ResourceDeposit, Task>();

	for (auto&& [entity, deposit, task] : depositTasks.each()) {
		float deltaWorkPercent = static_cast<float>(task.deltaWork / static_cast<double>(task.requiredWork));
		float resourceExtracted = deltaWorkPercent * deposit.massOfResource;

		int charactersAssigned = 0;

		auto characters = m_pRegistry->view<GameCharacter, CurrentTask>();
		for (auto&& [entity, character, task] : characters.each()) {
			if (task.taskEntity == entity) {
				charactersAssigned++;
			}
		}

		float characterShare = resourceExtracted / static_cast<float>(charactersAssigned);
		
		for (auto&& [entity, character, task] : characters.each()) {
			if (task.taskEntity == entity) {
				//m_pRegistry->emplace<
			}
		}


	}
}
	 