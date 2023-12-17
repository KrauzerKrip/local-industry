#pragma once

#include <glm/glm.hpp> 


struct Npc {
	float speed;

	Npc(float speed) : speed(speed) {}
};

struct Waypoint {
	glm::vec3 position;

	Waypoint(glm::vec3 position) : position(position) {}
};

struct NpcGraphVisualizerNode {
};

struct NpcGraphVisualizerEdge {};
