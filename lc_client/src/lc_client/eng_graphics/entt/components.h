#pragma once

#include <variant>
#include <entt/entity/registry.hpp>

struct Mesh {
	Mesh() = default;
	Mesh(const Mesh&) = default;
};

struct MaterialGl {
	int shaderProgram;

	MaterialGl() = default;
	MaterialGl(const int shaderProgram) : shaderProgram(shaderProgram) {};
	MaterialGl(const MaterialGl&) = default;
};

