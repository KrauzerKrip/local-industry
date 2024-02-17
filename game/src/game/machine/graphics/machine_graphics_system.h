#pragma once

#include <entt/entt.hpp>

#include <glm/glm.hpp>


class MachineGraphicsSystem {
public:
	MachineGraphicsSystem(entt::registry* pRegistry);

	void frame(float deltaTime);

private:
	entt::registry* m_pRegistry = nullptr;

	const static glm::vec4 BLUEPRINT_COLOR;
	const static glm::vec4 TASK_COLOR;
};
