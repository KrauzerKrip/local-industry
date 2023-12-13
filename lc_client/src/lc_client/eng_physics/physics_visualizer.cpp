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
		auto raycastEntities = m_pSceneRegistry->view<RaycastQuery>(entt::exclude<PrimitiveLine, Transform>);

		for (auto&& [entity, query] : raycastEntities.each()) {

			glm::vec3 endPoint = query.position + query.direction * 1000.0f;

			m_pSceneRegistry->emplace<PrimitiveLine>(entity, query.position, endPoint, glm::vec3(0.0, 0.0, 1.0));
		}

		auto raycastResultEntities =
		m_pSceneRegistry->view<RaycastResult>(entt::exclude<PrimitiveCube, Transform>);

		for (auto&& [entity, result] : raycastResultEntities.each()) {
			if (result.intersectionPoint.has_value()) {
				Transform transform(result.intersectionPoint.value(), glm::vec3(0, 0, 0), glm::vec3(0.1f, 0.1f, 0.1f));
				m_pSceneRegistry->emplace<PrimitiveCube>(entity, glm::vec3(1.0, 0.0, 0.0));
				m_pSceneRegistry->emplace<Transform>(entity, transform);
			}
		}
	}
	else {
		auto raycastEntities = m_pSceneRegistry->view<RaycastQuery, PrimitiveLine>();
		for (auto&& [entity, query, line] : raycastEntities.each()) {
			m_pSceneRegistry->remove<PrimitiveLine>(entity);
		}

		auto raycastResultEntities = m_pSceneRegistry->view<RaycastResult, PrimitiveCube, Transform>();
		for (auto&& [entity, query, cube, transform] : raycastResultEntities.each()) {
			m_pSceneRegistry->remove<PrimitiveCube>(entity);
			m_pSceneRegistry->remove<Transform>(entity);
		}
	}
}
