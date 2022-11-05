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
	int colorTexture;
	int normalMap;
	int aoTexture;
	int metallicTexture;

	MaterialGl() = default;
	MaterialGl(const int shaderProgram, const int colorTexture) : shaderProgram(shaderProgram), colorTexture(colorTexture) {};
	MaterialGl(const MaterialGl&) = default;
};

