#pragma once

#include <memory>

#include <entt/entt.hpp>

#include "npc_graph_visualizer.h"
#include "lc_client/tier0/conpar/parameters.h"
#include "lc_client/eng_world/world.h"


class NpcSystem {
public:
	NpcSystem(Parameters* pParameters, World* pWorld);

	void update();

private:
	void createPath(entt::registry& registry, entt::entity entity);

	Parameters* m_pParameters = nullptr;
	World* m_pWorld = nullptr;
	entt::registry* m_pRegistry = nullptr;
	
	NpcGraph* m_pNpcGraph;
	std::unique_ptr<NpcGraphVisualizer> m_npcGraphVisualizer;
};
