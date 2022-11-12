#pragma once

#include <variant>
#include <entt/entity/registry.hpp>
#include <lc_client/eng_graphics/texture.h>

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
	Texture* colorTexture;
	Texture* normalMap;
	Texture* aoTexture;
	Texture* metallicTexture;

	MaterialGl() = default;
	MaterialGl(const int shaderProgram, Texture* colorTexture, Texture* normalMap, Texture* aoTexture, Texture* metallicTexture)
		: shaderProgram(shaderProgram), colorTexture(colorTexture), normalMap(normalMap), aoTexture(aoTexture), metallicTexture(metallicTexture) {};
	MaterialGl(const MaterialGl&) = default;
};

