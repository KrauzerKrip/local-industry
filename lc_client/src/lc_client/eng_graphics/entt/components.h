#pragma once

#include <variant>
#include <entt/entity/registry.hpp>

struct Mesh {
	Mesh() = default;
	Mesh(const Mesh&) = default;
};

struct VaoGl {
	int vaoId;

	VaoGl() = default;
	VaoGl(const int vaoId) : vaoId(vaoId) {};
	VaoGl(const VaoGl&) = default;
};

struct MaterialGl {
	int shaderProgram;

	MaterialGl() = default;
	MaterialGl(const int shaderProgram) : shaderProgram(shaderProgram) {};
	MaterialGl(const MaterialGl&) = default;
};

