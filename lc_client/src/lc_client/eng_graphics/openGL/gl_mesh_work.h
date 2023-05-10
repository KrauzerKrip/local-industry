#pragma once

#include <vector>

#include "lc_client/eng_graphics/mesh_work.h"


class MeshWorkGl : public MeshWork {
public:
	MeshWorkGl(entt::registry* pUtilRegistry) : MeshWork(pUtilRegistry){};
	
	void loadMesh(entt::entity mesh);

private:
	unsigned int createVao(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
};
