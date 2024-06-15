#include "agriculture_control_system.h"

#include "game/agriculture/components.h"
#include "game/character/components.h"

#include "lc_client/eng_graphics/entt/components.h"
#include <game/machine/components.h>


AgricultureControlSystem::AgricultureControlSystem(entt::registry* pRegistry) { m_pRegistry = pRegistry; }

void AgricultureControlSystem::onAction(std::string action, entt::entity entity, glm::vec3 position, float distance) {
	if (action == "kb_build") {
		if (m_pRegistry->all_of<Harvestable>(entity)) {
			if (m_pRegistry->all_of<Task>(entity)) {
				removeTask(entity);
			}
			else {
				if (m_pRegistry->all_of<Connections>(entity)) {
					Connections& connections = m_pRegistry->get<Connections>(entity);
					for (auto& [resourceType, connection] : connections.inputs) {
						if (connection.entity.has_value()) {
							return;
						}
					}
					for (auto& [resourceType, connection] : connections.outputs) {
						if (connection.entity.has_value()) {
							return;
						}
					}
				}

				addTask(entity);
			}
		}
	}
}

void AgricultureControlSystem::onMouseMove(entt::entity entity, glm::vec3 position, float distance) {}

void AgricultureControlSystem::addTask(entt::entity entity) {
	m_pRegistry->emplace<TaskRequest>(entity, TaskRequest("Harvest"));
	m_pRegistry->emplace<LonerTask>(entity);
	m_pRegistry->emplace<Outline>(entity, Outline(glm::vec3(1, 1, 1), 0.025));
}

void AgricultureControlSystem::removeTask(entt::entity entity) {
	m_pRegistry->emplace<RemoveTaskRequest>(entity, RemoveTaskRequest());
	m_pRegistry->remove<Outline>(entity);
}
