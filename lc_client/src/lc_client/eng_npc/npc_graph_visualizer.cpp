#include "npc_graph_visualizer.h"

#include "components.h"

#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_scene/entt/components.h"


NpcGraphVisualizer::NpcGraphVisualizer(NpcGraph* pNpcGraph, Parameters* pParameters, entt::registry* pRegistry) { 
	m_pNpcGraph = pNpcGraph;
	m_pRegistry = pRegistry;

	ConPar<bool>& conpar = pParameters->getParameter<bool>("npc_show_graph");

	conpar.setCallback([this](bool value) {
		if (value) {
			buildGraph();
		}
		else {
			cleanGraph();
		}
	});
}

void NpcGraphVisualizer::buildGraph() { 
	cleanGraph();

	std::vector<npc::GraphNode> nodes = m_pNpcGraph->getNodes();
	std::vector<npc::GraphVertex> vertices = m_pNpcGraph->getVertices();

	for (npc::GraphNode& node : nodes) {
		entt::entity entity = m_pRegistry->create();

		PrimitiveCube gizmoCube(glm::vec4(0, 0, 1, 1));
		Transform transform(node.position, glm::vec3(0, 0, 0), glm::vec3(0.1, 0.1, 0.1));

		m_pRegistry->emplace<PrimitiveCube>(entity, gizmoCube);
		m_pRegistry->emplace<Transform>(entity, transform);
		m_pRegistry->emplace<NpcGraphVisualizerNode>(entity);
	}

	std::vector<unsigned int> previous;

	for (unsigned int i = 0; i < vertices.size(); i++) {
		npc::GraphVertex& vertex = vertices.at(i);
		for (unsigned int aI : vertex.adjacentVertices) {
			bool isPrevious = false;
			for (unsigned int pI : previous) {
				if (aI == pI) {
					isPrevious = true;
				}
			}

			if (!isPrevious) {
				glm::vec3 pos1 = m_pNpcGraph->getNode(i).position;
				glm::vec3 pos2 = m_pNpcGraph->getNode(aI).position;

				entt::entity entity = m_pRegistry->create();

				PrimitiveLine gizmoLine(pos1, pos2, glm::vec3(0, 1, 0));

				m_pRegistry->emplace<PrimitiveLine>(entity, gizmoLine);
				m_pRegistry->emplace<NpcGraphVisualizerEdge>(entity);
			}
		}

		previous.push_back(i);
	}
}

void NpcGraphVisualizer::cleanGraph() {
	auto visualNodeEntities = m_pRegistry->view<NpcGraphVisualizerNode>();
	auto visualEdgeEntities = m_pRegistry->view<NpcGraphVisualizerEdge>();
	for (auto&& [entity] : visualNodeEntities.each()) {
		m_pRegistry->destroy(entity);
	}
	for (auto&& [entity] : visualEdgeEntities.each()) {
		m_pRegistry->destroy(entity);
	}
}
