#pragma once

#include "lc_client/util/i_eng_resource.h"
#include <string>
#include <entt/entt.hpp>
#include "lc_client/eng_scene/scene_loading.h"
#include "lc_client/eng_npc/npc_graph.h"
#include "lc_client/eng_npc/npc_graph_loader/npc_graph_loader.h"


class World {
public:
	World(eng::IResource* pResource, SceneLoading* pSceneLoading);
	~World();

	void loadScene(std::string pack, std::string scene);
	void loadMap(std::string pack, std::string map);

	entt::registry& getRegistry();
	entt::registry& getUtilRegistry();
	NpcGraph* getNpcGraph();

private:
	entt::registry m_registry;
	entt::registry m_utilRegistry;

	std::unique_ptr<NpcGraph> m_npcGraph;

	SceneLoading* m_pSceneLoading = nullptr;
	eng::IResource* m_pResource = nullptr;
};
