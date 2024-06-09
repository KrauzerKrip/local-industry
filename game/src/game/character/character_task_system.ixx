module;

#include <iostream>

#include <entt/entt.hpp>

#include "game/machine/components.h"
#include "lc_client/eng_npc/components.h"
#include <lc_client/eng_model/entt/components.h>
#include <lc_client/eng_physics/entt/components.h>
#include "components.h"
#include "game/control/components.h"


export module character:character_task_system;
import :task_queue;

export class CharacterTaskSystem {
public:
	CharacterTaskSystem(entt::registry* pRegistry) { m_pRegistry = pRegistry; }

	void update() {
		processTaskRequests();
		processRemoveTaskRequests();
		assignTasksToCharacters();
		queueTasks();
		processTasks();
	}

	void processTaskRequests() {
		auto requests = m_pRegistry->view<TaskRequest>();

		for (auto&& [entity, request] : requests.each()) {
			m_pRegistry->emplace<Task>(entity, Task(request.name));
			m_pRegistry->emplace<AssignTaskRequest>(entity, AssignTaskRequest(request.maxExecutors, request.isLoner));

			m_pRegistry->remove<TaskRequest>(entity);
		}
	}

	void processRemoveTaskRequests() {
		auto requests = m_pRegistry->view<RemoveTaskRequest>();
		auto characters = m_pRegistry->view<GameCharacter>();

		for (auto&& [entity] : requests.each()) {
			m_pRegistry->remove<Task>(entity);

			if (m_pRegistry->all_of<CharacterAssignedTo>(entity)) {
				m_pRegistry->remove<CharacterAssignedTo>(entity);
			}

			for (auto&& [ent, character] : characters.each()) {
				if (m_pRegistry->all_of<CurrentTask>(ent)) {
					CurrentTask& currentTask = m_pRegistry->get<CurrentTask>(ent);
					if (currentTask.taskEntity == entity) {
						m_pRegistry->remove<CurrentTask>(ent);
					}
				}
			}

			if (m_pRegistry->all_of<Outline>(entity)) {
				m_pRegistry->remove<Outline>(entity); // TODO it should be better than this
			}

			m_pRegistry->remove<RemoveTaskRequest>(entity);
		}
	}

	// it may bug if there are more than one request (some request may be lost).
	void assignTasksToCharacters() {
		auto request = m_pRegistry->view<AssignTaskRequest>();
		auto characters = m_pRegistry->view<GameCharacter, Selected>();

		for (auto&& [entity, request] : request.each()) {
			unsigned int characterCount = 0;

			for (auto [charEnt, character] : characters.each()) {
				if (request.maxExecutors == 1) {
					m_pRegistry->emplace<CharacterAssignedTo>(entity, CharacterAssignedTo(charEnt));
				}

				if (characterCount < request.maxExecutors) {
					removeCharacterTasks(charEnt);
					m_pRegistry->emplace_or_replace<CurrentTask>(charEnt, entity);

					characterCount++;
				}
			}

			m_pRegistry->remove<AssignTaskRequest>(entity);
		}
	}

	void removeCharacterTasks(entt::entity charEnt) {
		if (m_pRegistry->all_of<CurrentTask>(charEnt)) {
			m_pRegistry->remove<CurrentTask>(charEnt);
		}

		TaskQueue& taskQueue = m_pRegistry->get<TaskQueue>(charEnt);

		taskQueue.forEach([this](entt::entity entity) { m_pRegistry->emplace<RemoveTaskRequest>(entity, RemoveTaskRequest()); });

		taskQueue.clear();
	}

	void queueTasks() {
		auto charactersWithTasks = m_pRegistry->view<GameCharacter, CurrentTask, TaskQueue>();

		for (auto&& [entity, character, currentTask, taskQueue] : charactersWithTasks.each()) {
			Task& task = m_pRegistry->get<Task>(currentTask.taskEntity);
			if (task.progress == TaskProgress::PLANNED) {
				if (taskQueue.push(currentTask.taskEntity)) {
					task.progress = TaskProgress::QUEUED;
				}
			}
		}
	}

	void processTasks() {
		auto characters = m_pRegistry->view<GameCharacter, TaskQueue, Transform, Colliders>();

		for (auto&& [entity, character, taskQueue, transform, colliders] : characters.each()) {
			auto task = taskQueue.getFront();
			if (task) {
				if (!m_pRegistry->valid(*task)) {
					taskQueue.pop();
					break;
				}
				if (!m_pRegistry->all_of<Transform, Task>(*task)) {
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
					m_pRegistry->remove<CurrentTask>(entity);
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