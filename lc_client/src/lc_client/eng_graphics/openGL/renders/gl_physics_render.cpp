#include "gl_physics_render.h"

#include "lc_client/eng_physics/entt/components.h"


PhysicsRender::PhysicsRender(entt::registry* pSceneRegisry, entt::registry* pMapRegistry) {
	m_pSceneRegistry = pSceneRegisry;
	m_pMapRegistry = pMapRegistry;
}

void PhysicsRender::render() { renderColliders(); }

void PhysicsRender::renderColliders() { 
	auto boxColliders = m_pSceneRegistry->view<BoxColliderVertices>();
}
