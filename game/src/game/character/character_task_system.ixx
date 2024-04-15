module;

#include <iostream>

#include <entt/entt.hpp>

#include "game/machine/components.h"
#include "lc_client/eng_npc/components.h"
#include <lc_client/eng_model/entt/components.h>
#include <lc_client/eng_physics/entt/components.h>
#include "components.h"


export module character:character_task_system;
import :task_queue;

export class CharacterTaskSystem {
public:
	CharacterTaskSystem(entt::registry* pRegistry) { m_pRegistry = pRegistry; }

	void update() { 
		queueTasks();
		processTasks();
	}

	void queueTasks() {
		auto assignedTasks = m_pRegistry->view<Transform, Task, CharacterAssignedTo>();

		for (auto&& [entity, transform, task, characterAssignedTo] : assignedTasks.each()) {
			TaskQueue& taskQueue = m_pRegistry->get<TaskQueue>(characterAssignedTo.entity);
			if (task.progress == TaskProgress::PLANNED) {
				if (taskQueue.push(entity)) {
					task.progress = TaskProgress::QUEUED;
				}
			}
		}
	}

	void processTasks() {
	    auto taskQueues = m_pRegistry->view<GameCharacter, TaskQueue, Transform, Colliders>();

		for (auto&& [entity, character, taskQueue, transform, colliders] : taskQueues.each()) {
			auto task = taskQueue.getFront();
			if (task) {
				if (!m_pRegistry->valid(*task)) {
					taskQueue.pop();
					break;
				}
				if (!m_pRegistry->all_of<Task, Transform>(*task)) {
					taskQueue.pop();
					break;
				}

			    Transform taskTransform = m_pRegistry->get<Transform>(*task);

				if (m_pRegistry->get<Task>(*task).progress == TaskProgress::QUEUED) {
					m_pRegistry->emplace_or_replace<Waypoint>(entity, Waypoint(taskTransform.position));
					m_pRegistry->get<Task>(*task).progress = TaskProgress::WAYPOINT;
				}

				if (glm::distance(transform.position, taskTransform.position) < getTaskAreaRadius(colliders)) {
					m_pRegistry->remove<Waypoint>(entity);
					m_pRegistry->get<Task>(*task).progress = TaskProgress::COMPLETED;
					taskQueue.pop();
				};
			}
		}
	}

	float getTaskAreaRadius(const Colliders& colliders) const {
		float maxDistance = 0;
		for (auto&& [entity, type] : colliders.colliders) {
			if (type == ColliderType::BOX) {
				Transform& transform = m_pRegistry->get<Transform>(entity);
				float distance = glm::distance(glm::vec3(0), glm::vec3(transform.scale.x, 0, transform.scale.y));
				maxDistance = std::max(distance, maxDistance);
			}
		}
		return maxDistance;
	}


private:
	entt::registry* m_pRegistry = nullptr;
};