#pragma once

#include <variant>
#include <entt/entity/registry.hpp>
#include <vector>
#include <glm/glm.hpp>

#include "lc_client/eng_graphics/texture.h"


struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texureCoords;
};

struct Mesh {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Mesh() = default;
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) : vertices(std::move(vertices)), indices(std::move(indices));
	Mesh(const Mesh&) = default;
};

struct VaoGl {
	unsigned int vaoId;

	VaoGl() = default;
	VaoGl(const int vaoId) : vaoId(vaoId) {};
	VaoGl(const VaoGl&) = default;
};

struct MaterialGl {
	unsigned int shaderProgram;
	Texture* colorTexture;
	Texture* normalMap;
	Texture* aoTexture;
	Texture* metallicTexture;

	MaterialGl() = default;
	MaterialGl(const int shaderProgram, Texture* colorTexture, Texture* normalMap, Texture* aoTexture, Texture* metallicTexture)
		: shaderProgram(shaderProgram), colorTexture(colorTexture), normalMap(normalMap), aoTexture(aoTexture), metallicTexture(metallicTexture) {};
	MaterialGl(const MaterialGl&) = default;
};

