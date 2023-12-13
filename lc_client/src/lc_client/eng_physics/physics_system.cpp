#include "physics_system.h"

#include <glm/gtc/matrix_transform.hpp>

#include "entt/components.h"
#include "raycast/plane.h"


void PhysicsSystem::update() { 
	updateVertices();
	updateRaycast();
}

void PhysicsSystem::updateVertices() {
	auto boxColliders = m_pSceneRegistry->view<BoxCollider, Transform>(entt::exclude<BoxColliderVertices>);

	for (auto&& [entity, box, transform] : boxColliders.each()) {
		BoxColliderVertices vertices;

		float minX = -box.length / 2;
		float maxX = box.length / 2;
		float minY = -box.height / 2;
		float maxY = box.height / 2;
		float minZ = -box.width / 2;
		float maxZ = box.width / 2;

		vertices.vertices.push_back(glm::vec3(minX, maxY, maxZ));
		vertices.vertices.push_back(glm::vec3(minX, minY, maxZ));
		vertices.vertices.push_back(glm::vec3(maxX, minY, maxZ));
		vertices.vertices.push_back(glm::vec3(maxX, maxY, maxZ));
		vertices.vertices.push_back(glm::vec3(minX, maxY, minZ));
		vertices.vertices.push_back(glm::vec3(minX, minY, minZ));
		vertices.vertices.push_back(glm::vec3(maxX, minY, minZ));
		vertices.vertices.push_back(glm::vec3(maxX, maxY, minZ));

		transformVertices(vertices.vertices, transform);

		m_pSceneRegistry->emplace<BoxColliderVertices>(entity, vertices);
	}
}

void PhysicsSystem::updateRaycast() {
	auto raycastQueries = m_pSceneRegistry->view<RaycastQuery>();

	for (auto&& [raycastEntity, query] : raycastQueries.each()) {
		auto boxColliders = m_pSceneRegistry->view<BoxCollider, Transform>();

		for (auto&& [ent,  boxCollider, transform] : boxColliders.each()) {
			Ray ray(query.position, query.direction);
			std::optional<glm::vec3> raycastResult = ray.getIntersectionWithOBB(boxCollider, transform);

			if (raycastResult.has_value()) {
				std::optional<entt::entity> optionalEnt = std::make_optional<entt::entity>(ent);
				std::optional<glm::vec3> optionaPos = std::make_optional<glm::vec3>(raycastResult.value());
				m_pSceneRegistry->emplace<RaycastResult>(raycastEntity, optionalEnt, optionaPos);
			}
		}
	}
}


void PhysicsSystem::transformVertices(std::vector<glm::vec3>& vertices, Transform& transform) {
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, transform.position);
	modelMatrix *= glm::mat4_cast(transform.rotation);
	modelMatrix = glm::scale(modelMatrix, transform.scale);

	for (glm::vec3& vertex : vertices) {
		glm::vec4 vert4 = modelMatrix * glm::vec4(vertex, 0);
		vertex.x = vert4.x;
		vertex.y = vert4.y;
		vertex.z = vert4.z;
	}
}
