#pragma once

#include "lc_client/util/i_eng_resource.h"

#include "lc_client/eng_npc/npc_graph.h"


class NpcGraphLoader {
public:
	NpcGraphLoader(eng::IResource* pResource);

	NpcGraph* getGraph(std::string descriptorPath);

private:
	eng::IResource* m_pResource = nullptr;
};
