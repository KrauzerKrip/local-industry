module;

#include <iostream>

#include <entt/entt.hpp>

#include "game/machine/components.h"
#include "lc_client/eng_npc/components.h"

export module character:character_task_system;
import :components;
import :task_queue;

export class CharacterTaskSystem {
public:
	CharacterTaskSystem(entt::registry* pRegistry) { m_pRegistry = pRegistry; }

	void update() { 
		auto assignedTasks = m_pRegistry->view<Blueprint, Transform, Task, CharacterAssignedTo>();
		
		for (auto&& [entity, transform, task, characterAssignedTo] : assignedTasks.each()) {
			//m_pRegistry->emplace_or_replace<Waypoint>(characterAssignedTo.entity, Waypoint(transform.position));
			TaskQueue& taskQueue = m_pRegistry->get<TaskQueue>(characterAssignedTo.entity);
			if (!task.addedToQueue) {
				taskQueue.push(entity);
				task.addedToQueue = true;
			}
		}

		processTasks();
	}

	void processTasks() {
	    auto taskQueues = m_pRegistry->view<GameCharacter, TaskQueue>();
		
	}



private:
	entt::registry* m_pRegistry = nullptr;
};