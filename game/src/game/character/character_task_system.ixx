module;

#include <iostream>

#include <entt/entt.hpp>

#include "game/machine/components.h"
#include "lc_client/eng_npc/components.h"
#include <lc_client/eng_model/entt/components.h>

export module character:character_task_system;
import :components;
import :task_queue;

export class CharacterTaskSystem {
public:
	CharacterTaskSystem(entt::registry* pRegistry) { m_pRegistry = pRegistry; }

	void update() { 
		auto assignedTasks = m_pRegistry->view<Blueprint, Transform, Task, CharacterAssignedTo>();
		
		for (auto&& [entity, transform, task, characterAssignedTo] : assignedTasks.each()) {
			TaskQueue& taskQueue = m_pRegistry->get<TaskQueue>(characterAssignedTo.entity);
			if (task.progress == TaskProgress::PLANNED) {
				taskQueue.push(entity);
				task.progress = TaskProgress::QUEUED;
			}
		}

		processTasks();
	}

	void processTasks() {
	    auto taskQueues = m_pRegistry->view<GameCharacter, TaskQueue, Transform>();

		for (auto&& [entity, character, taskQueue, transform] : taskQueues.each()) {
			auto task = taskQueue.getFront();
			if (task) {
				if (!m_pRegistry->valid(*task)) {
					taskQueue.pop();
					break;
				}
				if (!m_pRegistry->all_of<Blueprint, Task, Transform>(*task)) {
					taskQueue.pop();
					break;
				}

			    Transform taskTransform = m_pRegistry->get<Transform>(*task);

				if (m_pRegistry->get<Task>(*task).progress == TaskProgress::QUEUED) {
					m_pRegistry->emplace_or_replace<Waypoint>(entity, Waypoint(taskTransform.position));
					m_pRegistry->get<Task>(*task).progress = TaskProgress::WAYPOINT;
				}

				if (glm::distance(transform.position, taskTransform.position) < 2) {
					m_pRegistry->remove<Waypoint>(entity);
					m_pRegistry->get<Task>(*task).progress = TaskProgress::COMPLETED;
				};
			}
		}
	}




private:
	entt::registry* m_pRegistry = nullptr;
};