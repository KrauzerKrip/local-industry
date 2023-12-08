#pragma once

#include <vector>

#include "lc_client/eng_graphics/mesh_loader.h"


class MeshLoaderGl : public MeshLoader {
public:
	MeshLoaderGl() {};
	
	void loadMesh(entt::registry* pUtilRegistry, entt::entity mesh);

private:
	unsigned int createVao(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
};
