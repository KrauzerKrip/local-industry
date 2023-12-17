#pragma once

#include <glm/glm.hpp>

#include <list>
#include <vector>


namespace npc {

	struct GraphNode {
		glm::vec3 position;
	};

	struct GraphVertex {
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
	NpcGraph(std::vector<npc::GraphVertex> vertices, std::vector<GraphNode> nodes);
	
	Path getShortestPath(unsigned int source, unsigned int destination);
	//Path getShortestPathQueue(unsigned int source, unsigned int destination);
	unsigned int getClosestVertice(glm::vec3 position) const;
	const GraphNode& getNode(unsigned int vertice) const;
	const std::vector<GraphNode>& getNodes();
	const std::vector<npc::GraphVertex>& getVertices();

private:
	float getDistance(unsigned int source, unsigned int destination);

	void addEdge(unsigned int source, unsigned int destination);
	void addNode(unsigned int vertice, GraphNode node);

	const std::vector<npc::GraphVertex> m_vertices;
	const std::vector<npc::GraphNode> m_nodes;
};
