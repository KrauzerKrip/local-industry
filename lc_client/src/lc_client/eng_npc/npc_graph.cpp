#include "npc_graph.h"

#include <queue>


NpcGraph::NpcGraph(std::vector<npc::Vertice> vertices, std::vector<npc::Node> nodes) : m_vertices(vertices), m_nodes(nodes) {
	
}

Path NpcGraph::getShortestPath(unsigned int source, unsigned int destination) {
	assert(m_vertices.size() < UINT_MAX, "NpcGraph: too much vertices.");

	std::vector<unsigned int> vertices;
	std::vector<float> distances(m_vertices.size());
	std::vector<unsigned int> previous(m_vertices.size());


	for (unsigned int i = 0; i < m_vertices.size(); i++) {
		distances[i] = INFINITY;
		vertices.push_back(i);
	}

	distances[source] = 0;
	float alt = distances[source];

	unsigned int vertices_size = (unsigned int)vertices.size();

	while (vertices_size > 0) {
		unsigned int minDistVertex = INFINITY; 
		float minDist = INFINITY;			  
		for (unsigned int i = 0; i < distances.size(); i++) {
			bool isVerticeInVertices = false;

			if (vertices[i] != UINT_MAX) {
				isVerticeInVertices = true;
			}

			if ((distances[i] < minDist) && isVerticeInVertices) {
				minDistVertex = i;
				minDist = distances[i];
			}
		}

		vertices[minDistVertex] = UINT_MAX;
		vertices_size--;

		if (minDistVertex == destination) {
			break;
		}

		for (unsigned int adjVertex : m_vertices[minDistVertex].adjacentVertices) {
			if (vertices[adjVertex] != UINT_MAX) {
				alt = distances[minDistVertex] + getDistance(minDistVertex, adjVertex);

				if (alt < distances[adjVertex]) {
					distances[adjVertex] = alt;
					previous[adjVertex] = minDistVertex;
				}
			}
		}
	}

	std::vector<unsigned int> path;
	float distance = distances[destination];

	if (distance != INFINITY) {
		unsigned int current = destination;
		while (current != source) {
			path.push_back(current);
			current = previous[current];
		}
		path.push_back(source);
		std::reverse(path.begin(), path.end());
	}

	return Path(path, distance);
}


const Node& NpcGraph::getClosestNode(glm::vec3 position) { return Node(); }

unsigned int NpcGraph::getVertice(Node& node) { return 0; }

const Node& NpcGraph::getNode(unsigned int vertice) { return m_nodes.at(vertice); }

float NpcGraph::getDistance(unsigned int source, unsigned int destination) { 
	Node node1 = getNode(source);
	Node node2 = getNode(destination);

	return glm::distance(node1.position, node2.position);
}

//void NpcGraph::addEdge(unsigned int source, unsigned int destination) {
//	m_vertices.at(source).adjacentVertices.push_back(destination);
//	m_vertices.at(destination).adjacentVertices.push_back(source);
//}
//
//void NpcGraph::addNode(unsigned int vertice, npc::Node node) { 
//	m_nodes[vertice] = node;
//}