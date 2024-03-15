#include "collider_system.h"

#include "entt/components.h"
#include "lc_client/eng_scene/entt/components.h" 
#include <glm/gtx/string_cast.hpp>



ColliderSystem::ColliderSystem(entt::registry* pRegistry) { m_pRegistry = pRegistry; }

void ColliderSystem::update() { 
	auto colliderOwnersEntities = m_pRegistry->view<Colliders, Transform>();
	
	for (auto&& [entity, colliders, ownerTransform] : colliderOwnersEntities.each()) {
		for (auto&& [ent, type] : colliders.colliders) {
			Transform& transform = m_pRegistry->get<Transform>(ent);
			const RelativeTransform& relativeTransform = m_pRegistry->get<RelativeTransform>(ent);

			glm::quat quat = ownerTransform.rotation;
			glm::vec4 pos4(relativeTransform.transform.position, 0.0);
			pos4 = glm::toMat4(quat) * pos4;

			glm::mat4 scaleMatrix(1.0f);
			glm::vec3 scaleVector(ownerTransform.scale.x, ownerTransform.scale.y, ownerTransform.scale.z);
			scaleMatrix = glm::scale(scaleMatrix, scaleVector);

			transform.position = ownerTransform.position + glm::vec3((pos4 * scaleMatrix));
			transform.rotation = relativeTransform.transform.rotation * ownerTransform.rotation;
			transform.scale = ownerTransform.scale * relativeTransform.transform.scale;
		}
	}
}
