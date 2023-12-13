#include "physics_visualizer.h"

#include "lc_client/eng_physics/entt/components.h"
#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_scene/entt/components.h"


PhysicsVisualizer::PhysicsVisualizer(Parameters* pParameters, entt::registry* pSceneRegistry, entt::registry* pMapRegistry) {
	m_pParameters = pParameters;

	m_pSceneRegistry = pSceneRegistry;
	m_pMapRegistry = pMapRegistry;
}

void PhysicsVisualizer::update() { 
	if (m_pParameters->getParameterValue<bool>("ph_debug_mode")) {
		auto raycastEntities = m_pSceneRegistry->view<RaycastQuery>(entt::exclude<PrimitiveLine, PrimitiveCube, Transform>);

		for (auto&& [entity, query] : raycastEntities.each()) {

			glm::vec3 endPoint = query.position + query.direction * 1000.0f;

			m_pSceneRegistry->emplace<PrimitiveLine>(entity, query.position, endPoint, glm::vec3(0.0, 0.0, 1.0));
		}
	}
}
