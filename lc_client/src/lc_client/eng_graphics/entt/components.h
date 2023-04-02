#pragma once

#include <variant>
#include <entt/entity/registry.hpp>
#include <vector>
#include <glm/glm.hpp>

#include "lc_client/eng_graphics/texture.h"


struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoords;
};

struct Mesh {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	entt::entity* material;
	int vaoId;

	Mesh() = default;
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, entt::entity& material)
		: vertices(std::move(vertices)), indices(std::move(indices)), material(&material) {};
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, entt::entity& material, int vaoId)
		: vertices(std::move(vertices)), indices(std::move(indices)), material(&material), vaoId() {};
	Mesh(const Mesh& mesh) : vertices(std::move(mesh.vertices)), indices(std::move(mesh.indices)), material(mesh.material), vaoId(mesh.vaoId) {};
};

struct VaoGl {
	unsigned int vaoId;

	VaoGl() = default;
	VaoGl(const int vaoId) : vaoId(vaoId) {};
	VaoGl(const VaoGl&) = default;
};

struct MaterialMR {
	Shader shader;
	Texture* colorTexture;
	Texture* normalMap;
	Texture* aoTexture;
	Texture* metallicTexture;

	MaterialMR() = default;
	MaterialMR(Shader shader, Texture* colorTexture, Texture* normalMap, Texture* aoTexture, Texture* metallicTexture)
		: shader(shader), colorTexture(colorTexture), normalMap(normalMap), aoTexture(aoTexture), metallicTexture(metallicTexture) {};
	MaterialMR(const MaterialMR&) = default;
};

struct MaterialSG {
	Shader shader;
	Texture* diffuseTexture;
	Texture* specularTexture;
	Texture* glossinessTexture;
	Texture* normalMap;
	Texture* aoTexture;

	MaterialSG() = default;
	MaterialSG(Shader shader, Texture* diffuseTexture, Texture* specularTexture, Texture* glossinessTexture, Texture* normalMap, Texture* aoTexture)
		: shader(shader), diffuseTexture(diffuseTexture), specularTexture(specularTexture), glossinessTexture(glossinessTexture), normalMap(normalMap), aoTexture(aoTexture) {};
	MaterialSG(const MaterialSG&) = default;
};


struct Shader {
	entt::entity* shader;

	Shader() = default;
	Shader(entt::entity* shader) : shader(shader) {};
	Shader(const Shader&) = default;
};

struct ShaderGl {
	unsigned int shaderProgram;

	ShaderGl() = default;
	ShaderGl(const int shaderProgram) : shaderProgram(shaderProgram){};
	ShaderGl(const ShaderGl&) = default;
};

