#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include "lc_client/eng_scene/entt/components.h"
#include "raycast/ray.h"


class PhysicsSystem {
public:
	PhysicsSystem(entt::registry* pSceneRegistry, entt::registry* pMapRegistry);

	void update();

private:
	void updateVertices();
	void updateRaycast();
	void transformVertices(std::vector<glm::vec3>& vertices, Transform& transform);

	entt::registry* m_pSceneRegistry = nullptr;
	entt::registry* m_pMapRegistry = nullptr;
};
