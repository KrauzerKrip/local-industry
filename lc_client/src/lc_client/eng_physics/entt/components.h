#pragma once

#include <vector>
#include <optional>

#include <glm/glm.hpp>
#include <entt/entt.hpp>


struct BoxCollider {
	float length;
	float height;
	float width;

	BoxCollider(float length, float height, float width) : length(length), width(width), height(height){};
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

	RaycastResult(std::optional<entt::entity> entityIntersectedWith, std::optional<glm::vec3> intersectionPoint)
		: entityIntersectedWith(entityIntersectedWith),
		  intersectionPoint(intersectionPoint){};
};

