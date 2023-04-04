#pragma once

#include <vector>

#include <entt/entt.hpp>

#include "lc_client/eng_graphics/entt/components.h"


struct Model {
	std::vector<entt::entity> meshes;

	Model() = default;
	Model(std::vector<entt::entity> meshes) : meshes(meshes) {};
	Model(const Model&) = default;
};
