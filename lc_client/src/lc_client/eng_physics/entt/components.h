#pragma once

#include <vector>
#include <optional>
#include <string>
#include <tuple>

#include <glm/glm.hpp>
#include <entt/entt.hpp>


enum class ColliderType {
	BOX,
	AABB,
	SPHERE,
	CAPSULE
};


struct PhysicsRequest {
	std::string filePath;

	PhysicsRequest(std::string filePath) : filePath(filePath) {}
};

struct Colliders {
	std::vector<std::tuple<entt::entity, ColliderType>> colliders;
};

struct BoxCollider {
}; 

                             
/*	 4-----------7            Y
	/ |         /|            | 
	0----------3 |            |
	| 5        | 6            0-------X
	|/		   |/            /
   	1----------2      	    /
						   Z

*/						 
struct BoxColliderVertices {
	std::vector<glm::vec3> vertices;
};

struct RaycastQuery {
	glm::vec3 position;
	glm::vec3 direction;

	RaycastQuery(glm::vec3 position, glm::vec3 direction) : position(position), direction(direction){};
};

struct RaycastResult {
	std::optional<entt::entity> entityIntersectedWith;
	std::optional<glm::vec3> intersectionPoint;
	std::optional<float> intersectionDistance;

	RaycastResult(std::optional<entt::entity> entityIntersectedWith, std::optional<glm::vec3> intersectionPoint,
		std::optional<float> intersectionDistance)
		: entityIntersectedWith(entityIntersectedWith),
		  intersectionPoint(intersectionPoint),
		  intersectionDistance(intersectionDistance){};
};

