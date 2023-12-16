#include "physics_system.h"

#include <glm/gtc/matrix_transform.hpp>

#include "entt/components.h"
#include "raycast/plane.h"


PhysicsSystem::PhysicsSystem(Parameters* pParameters, entt::registry* pRegistry) : m_physicsVisualizer(pParameters, pRegistry) {
	m_pRegistry = pRegistry;
}

void PhysicsSystem::update() { 
	updateVertices();
	updateRaycast();

	m_physicsVisualizer.update();
}

void PhysicsSystem::updateVertices() {
	auto boxColliders = m_pRegistry->view<BoxCollider, Transform>(entt::exclude<BoxColliderVertices>);

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

		m_pRegistry->emplace<BoxColliderVertices>(entity, vertices);
	}
}

void PhysicsSystem::updateRaycast() {
	auto raycastQueries = m_pRegistry->view<RaycastQuery>(entt::exclude<RaycastResult>);

	for (auto&& [raycastEntity, query] : raycastQueries.each()) {
		std::unordered_map<entt::entity, RaycastIntersection> intersections = getIntersections(query);

		if (intersections.size() > 0) {
			auto intersection = getMinimumDistanceIntersection(intersections);

			auto optionalEntity = std::make_optional<entt::entity>(intersection.first);
			auto optionalPoint = std::make_optional<glm::vec3>(intersection.second.point);
			auto optionalDistance = std::make_optional<float>(intersection.second.distance);

			m_pRegistry->emplace<RaycastResult>(
				raycastEntity, RaycastResult(optionalEntity, optionalPoint, optionalDistance));
		}
		else {
			m_pRegistry->emplace<RaycastResult>(
				raycastEntity, RaycastResult(std::nullopt, std::nullopt, std::nullopt));
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

std::unordered_map<entt::entity, RaycastIntersection> PhysicsSystem::getIntersections(RaycastQuery query) {
	auto boxColliders = m_pRegistry->view<BoxCollider, Transform>();

	std::unordered_map<entt::entity, RaycastIntersection> intersections;

	for (auto&& [ent, boxCollider, transform] : boxColliders.each()) {
		Ray ray(query.position, query.direction);
		std::optional<RaycastIntersection> raycastResult = ray.getIntersectionWithOBB(boxCollider, transform);

		if (raycastResult.has_value()) {
			intersections.emplace(ent, raycastResult.value());
		}
	}

	return intersections;
}

std::pair<entt::entity, RaycastIntersection> PhysicsSystem::getMinimumDistanceIntersection(
	std::unordered_map<entt::entity, RaycastIntersection>& intersections) {

	auto firstElement = *intersections.begin();

	entt::entity minDistanceEntity = firstElement.first;
	RaycastIntersection minRaycastIntersection(firstElement.second.point, firstElement.second.distance);

	for (auto& [ent, raycastIntersection] : intersections) {
		if (raycastIntersection.distance < minRaycastIntersection.distance) {
			minDistanceEntity = ent;
			minRaycastIntersection = raycastIntersection;
		}
	}

	return std::pair<entt::entity, RaycastIntersection>(minDistanceEntity, minRaycastIntersection);
}
