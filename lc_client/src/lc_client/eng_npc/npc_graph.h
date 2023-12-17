#pragma once

#include <glm/glm.hpp>

#include <list>
#include <vector>


namespace npc {

	struct Node {
		glm::vec3 position;
	};

	struct Vertice {
		std::list<unsigned int> adjacentVertices;
	};

	struct Path {
		std::vector<unsigned int> vertices;
		float distance;
	};
}

using namespace npc;

class NpcGraph {
public:
	NpcGraph(std::vector<Vertice> vertices, std::vector<Node> nodes);
	
	Path getShortestPath(unsigned int source, unsigned int destination);
	//Path getShortestPathQueue(unsigned int source, unsigned int destination);
	unsigned int getClosestVertice(glm::vec3 position) const;
	const Node& getNode(unsigned int vertice) const;

private:
	float getDistance(unsigned int source, unsigned int destination);

	void addEdge(unsigned int source, unsigned int destination);
	void addNode(unsigned int vertice, Node node);

	const std::vector<Vertice> m_vertices;
	const std::vector<Node> m_nodes;
};
