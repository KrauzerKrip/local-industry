#include "npc_graph_loader.h"

#include <nlohmann/json.hpp>

#include "lc_client/exceptions/io_exceptions.h"


using json = nlohmann::json;

NpcGraphLoader::NpcGraphLoader(eng::IResource* pResource) { m_pResource = pResource; }

NpcGraph NpcGraphLoader::getGraph(std::string descriptorPath) { 
	std::vector<npc::GraphVertex> vertices;
	std::vector<npc::GraphNode> nodes; 

	std::vector<unsigned char> buffer;

	buffer = m_pResource->getFileResource(descriptorPath);

	auto descriptor = json::parse(buffer);

	auto& verticesJson = descriptor.at("vertices");
	for (auto& verticeJson : verticesJson.items()) {
		npc::GraphVertex vertice;
		auto& adjacentVerticesJson = verticeJson.value();
		for (auto& adjacentVerticeJson : adjacentVerticesJson.items()) {
			unsigned int adjacentVertice = adjacentVerticeJson.value().get<unsigned int>();
			vertice.adjacentVertices.push_back(adjacentVertice);
		}
		vertices.push_back(vertice);
	}

	auto nodesJson = descriptor.at("nodes");
	for (auto& nodeJson : nodesJson.items()) {
		npc::GraphNode node;
	}

	return NpcGraph(vertices, nodes);
}
