#include "physics_visualizer.h"

#include "lc_client/eng_physics/entt/components.h"
#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_scene/entt/components.h"


PhysicsVisualizer::PhysicsVisualizer(Parameters* pParameters, entt::registry* pRegistry) {
	m_pParameters = pParameters;

	m_pRegistry = pRegistry;
}

void PhysicsVisualizer::update() { 
	if (m_pParameters->getParameterValue<bool>("ph_debug_mode")) {
		auto raycastEntities = m_pRegistry->view<RaycastQuery>(entt::exclude<PrimitiveLine, Transform>);

		for (auto&& [entity, query] : raycastEntities.each()) {

			glm::vec3 endPoint = query.position + query.direction * 1000.0f;

			m_pRegistry->emplace<PrimitiveLine>(entity, query.position, endPoint, glm::vec3(0.0, 0.0, 1.0));
		}

		auto raycastResultEntities =
		m_pRegistry->view<RaycastResult>(entt::exclude<PrimitiveCube, Transform>);

		for (auto&& [entity, result] : raycastResultEntities.each()) {
			if (result.intersectionPoint.has_value()) {
				Transform transform(result.intersectionPoint.value(), glm::vec3(0,  0, 0), glm::vec3(0.1f, 0.1f, 0.1f));
				m_pRegistry->emplace<PrimitiveCube>(entity, glm::vec4(1.0, 0.0, 0.0, 1));
				m_pRegistry->emplace<Transform>(entity, transform);
			}
		}
	}
	else {
		auto raycastEntities = m_pRegistry->view<RaycastQuery, PrimitiveLine>();
		for (auto&& [entity, query, line] : raycastEntities.each()) {
			m_pRegistry->remove<PrimitiveLine>(entity);
		}

		auto raycastResultEntities = m_pRegistry->view<RaycastResult, PrimitiveCube, Transform>();
		for (auto&& [entity, query, cube, transform] : raycastResultEntities.each()) {
			m_pRegistry->remove<PrimitiveCube>(entity);
			m_pRegistry->remove<Transform>(entity);
		}
	}

	if (m_pParameters->getParameterValue<bool>("ph_show_colliders")) {
		auto boxColliderEntities = m_pRegistry->view<BoxCollider>(entt::exclude<PrimitiveCube>);
		for (auto&& [entity] : boxColliderEntities.each()) {
			m_pRegistry->emplace<PrimitiveCube>(entity, PrimitiveCube(glm::vec4(0, 1, 0, 0.5)));
		}
	}
	else {
		auto boxColliderEntities = m_pRegistry->view<BoxCollider, PrimitiveCube>();
		for (auto&& [entity, boxCollider] : boxColliderEntities.each()) {
			m_pRegistry->remove<PrimitiveCube>(entity);
		}
	}
}
