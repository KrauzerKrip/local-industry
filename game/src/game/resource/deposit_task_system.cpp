#include "deposit_task_system.h"

#include "components.h"
#include "exceptions.h"
#include "game/character/components.h"
#include "game/inventory/components.h"


DepositTaskSystem::DepositTaskSystem(entt::registry* pRegistry, IConsole* pConsole) { 
	m_pRegistry = pRegistry;
	m_pConsole = pConsole;
 }

void DepositTaskSystem::update(double updateInterval) { 
	auto characters = m_pRegistry->view<GameCharacter, Inventory>();
	for (auto&& [charEnt, character, inventory] : characters.each()) {
		if (m_pRegistry->all_of<Extracted>(charEnt)) {
			// TODO: handle Extraced with e.g. animation
			m_pRegistry->remove<Extracted>(charEnt);
		}
		if (m_pRegistry->all_of<CantExtract>(charEnt)) {
			// TODO: handle CantExtract with GUI
			m_pRegistry->remove<CantExtract>(charEnt);
		}
	}

	auto depositTasks = m_pRegistry->view<ResourceDeposit, Task>();
	for (auto&& [depositEntity, deposit, task] : depositTasks.each()) {
		float deltaWorkPercent = static_cast<float>(task.deltaWork / static_cast<double>(task.requiredWork));
		float resourceExtracted = deltaWorkPercent * deposit.massOfResource;

		if (resourceExtracted > 0) {
			int i = 0;
		}

		int charactersAssigned = 0;

		auto charactersWithTasks = m_pRegistry->view<GameCharacter, CurrentTask, Inventory>();
		for (auto&& [ent, character, task, inventory] : charactersWithTasks.each()) {
			if (task.taskEntity == depositEntity) {
				charactersAssigned++;
			}
		}

		float characterShare = resourceExtracted / static_cast<float>(charactersAssigned);
		
		for (auto&& [charEnt, character, task, inventory] : charactersWithTasks.each()) {
			if (task.taskEntity == depositEntity) {
				m_pRegistry->emplace<ExtractRequest>(charEnt, ExtractRequest(depositEntity, characterShare));
			}
		}
	}
}
	 