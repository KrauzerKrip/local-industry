#include "npc_graph_test.h"

using namespace npc;

void NpcGraphTest::SetUp() { 
	std::vector<Vertice> vertices;
	std::vector<Node> nodes;

	Vertice vert0;
	Vertice vert1; 
	Vertice vert2;
	Vertice vert3;
	Vertice vert4;

	vert0.adjacentVertices.push_back(1);
	vert0.adjacentVertices.push_back(2);

	vert1.adjacentVertices.push_back(0);
	vert1.adjacentVertices.push_back(3);

	vert2.adjacentVertices.push_back(0);
	vert2.adjacentVertices.push_back(3);

	vert3.adjacentVertices.push_back(1);
	vert3.adjacentVertices.push_back(2);

	vert4.adjacentVertices.push_back(0);
	vert4.adjacentVertices.push_back(3);

	vertices.push_back(vert0);
	vertices.push_back(vert1);
	vertices.push_back(vert2);
	vertices.push_back(vert3);
	vertices.push_back(vert4);

	Node node0;
	Node node1;
	Node node2;
	Node node3;
	Node node4;

	node0.position = glm::vec3(0, 0, 0);
	node1.position = glm::vec3(5, 0, 5);
	node2.position = glm::vec3(5, 0, 0);
	node3.position = glm::vec3(10, 0, 0);
	node4.position = glm::vec3(-10, 0, -10);

	nodes.push_back(node0);
	nodes.push_back(node1);
	nodes.push_back(node2);
	nodes.push_back(node3);
	nodes.push_back(node4);

	m_pNpcGraph = new NpcGraph(vertices, nodes);
}

void NpcGraphTest::TearDown() { delete m_pNpcGraph; }
