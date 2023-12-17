#pragma once

#include <entt/entt.hpp>

#include "npc_graph.h"
#include "lc_client/tier0/conpar/parameters.h"


class NpcGraphVisualizer {
public:
	NpcGraphVisualizer(NpcGraph* pNpcGraph, Parameters* pParameters, entt::registry* pRegistry);

private:
	void buildGraph();
	void cleanGraph();

	NpcGraph* m_pNpcGraph = nullptr;
	entt::registry* m_pRegistry = nullptr;
};
