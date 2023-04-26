#pragma once

#include <vector>
#include <iostream>

#include <entt/entt.hpp>

#include "lc_client/eng_graphics/entt/components.h"


struct Model {
	std::vector<entt::entity> meshes;

	Model() = default;
	Model(std::vector<entt::entity> meshes) : meshes(meshes){};
	~Model() {}
	Model(const Model&) = default;
};
