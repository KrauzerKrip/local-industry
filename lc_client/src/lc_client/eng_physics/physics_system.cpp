#include "physics_system.h"

#include <glm/gtc/matrix_transform.hpp>

#include "entt/components.h"
#include "raycast/plane.h"


PhysicsSystem::PhysicsSystem(Physics* pPhysics, PhysicsLoader* pPhysicsLoader, Parameters* pParameters,
	entt::registry* pRegistry, IConsole* pConsole)
	: m_physicsVisualizer(pParameters, pRegistry),
	  m_physicsLoadingSystem(pPhysicsLoader, pRegistry, pConsole) {
	m_pPhysics = pPhysics;
	m_pRegistry = pRegistry;
}

void PhysicsSystem::update() { 
	updateVertices();
	updateRaycast();

	m_physicsVisualizer.update();
	m_physicsLoadingSystem.update();
}

void PhysicsSystem::updateVertices() {
	auto boxColliders = m_pRegistry->view<BoxCollider, Transform>(entt::exclude<BoxColliderVertices>);

	//for (auto&& [entity, box, transform] : boxColliders.each()) {
	//	BoxColliderVertices vertices;

	//	float minX = -box.length / 2;
	//	float maxX = box.length / 2;
	//	float minY = -box.height / 2;
	//	float maxY = box.height / 2;
	//	float minZ = -box.width / 2;
	//	float maxZ = box.width / 2;

	//	vertices.vertices.push_back(glm::vec3(minX, maxY, maxZ));
	//	vertices.vertices.push_back(glm::vec3(minX, minY, maxZ));
	//	vertices.vertices.push_back(glm::vec3(maxX, minY, maxZ));
	//	vertices.vertices.push_back(glm::vec3(maxX, maxY, maxZ));
	//	vertices.vertices.push_back(glm::vec3(minX, maxY, minZ));
	//	vertices.vertices.push_back(glm::vec3(minX, minY, minZ));
	//	vertices.vertices.push_back(glm::vec3(maxX, minY, minZ));
	//	vertices.vertices.push_back(glm::vec3(maxX, maxY, minZ));

	//	transformVertices(vertices.vertices, transform);

	//	m_pRegistry->emplace<BoxColliderVertices>(entity, vertices);
	//}
}

void PhysicsSystem::updateRaycast() {
	auto raycastQueries = m_pRegistry->view<RaycastQuery>(entt::exclude<RaycastResult>);

	for (auto&& [raycastEntity, query] : raycastQueries.each()) {
		RaycastResult result = m_pPhysics->raycast(query);
		m_pRegistry->emplace<RaycastResult>(raycastEntity, result);
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

