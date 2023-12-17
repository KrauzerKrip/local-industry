#pragma once

#include <memory>

#include <entt/entt.hpp>

#include "npc_graph_visualizer.h"
#include "lc_client/tier0/conpar/parameters.h"


class NpcSystem {
public:
	NpcSystem(Parameters* pParameters, entt::registry* pRegistry);

	void update();
	void setNpcGraph(NpcGraph* pNpcGraph);

private:
	Parameters* m_pParameters = nullptr;
	entt::registry* m_pRegistry = nullptr;
	
	std::unique_ptr<NpcGraph> m_npcGraph;
	std::unique_ptr<NpcGraphVisualizer> m_npcGraphVisualizer;
};
