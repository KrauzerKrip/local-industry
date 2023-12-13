#pragma once

#include <entt/entt.hpp>


class PhysicsRender {
public:
	PhysicsRender(entt::registry* pSceneRegisry, entt::registry* pMapRegistry);

	void render();

private:
	void renderColliders();

	entt::registry* m_pSceneRegistry = nullptr;
	entt::registry* m_pMapRegistry = nullptr;
};
