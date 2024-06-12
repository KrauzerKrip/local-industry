#include "machine_graphics_system.h"

#include "game/machine/components.h"
#include "lc_client/eng_graphics/entt/components.h"
#include "game/character/components.h"

#include "game/character/task_queue.h"


MachineGraphicsSystem::MachineGraphicsSystem(entt::registry* pRegistry) { m_pRegistry = pRegistry; }

void MachineGraphicsSystem::frame(float deltaTime) {
	auto blueprints = m_pRegistry->view<Blueprint, ShaderUniforms>(entt::exclude<Task>);
	for (auto&& [entity, uniforms] : blueprints.each()) {
		uniforms.vectorUniforms["color"] = BLUEPRINT_COLOR;
	}

	auto tasks = m_pRegistry->view<Blueprint, Task, ShaderUniforms>();
	for (auto&& [entity, task, uniforms] : tasks.each()) {
		uniforms.vectorUniforms["color"] = TASK_COLOR;
	}
}

const glm::vec4 MachineGraphicsSystem::BLUEPRINT_COLOR = glm::vec4(48.0 / 255.0, 87.0 / 255.0, 225.0 / 255.0, 0.5);
const glm::vec4 MachineGraphicsSystem::TASK_COLOR = glm::vec4(65.0 / 255.0, 170.0 / 255.0, 25.0 / 255.0, 0.75);