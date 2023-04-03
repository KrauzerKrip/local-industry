#pragma once

#include <vector>

#include "lc_client/eng_graphics/entt/components.h"


struct Model {
	std::vector<Mesh> meshes;

	Model() = default;
	Model(std::vector<Mesh> meshes) : meshes(meshes) {};
	Model(const Model&) = default;
};
