#pragma once

#include <vector>

#include <glm/glm.hpp> 

#include "npc_graph.h"


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

struct NpcPath {
	npc::GraphPath graphPath;
	glm::vec3 endPoint;
	unsigned int pointer;

	NpcPath(npc::GraphPath path, glm::vec3 endPoint) : graphPath(path), endPoint(endPoint), pointer(0) {}
};
