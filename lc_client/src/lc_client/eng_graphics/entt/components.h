#pragma once

#include <variant>
#include <entt/entity/registry.hpp>
#include <vector>
#include <glm/glm.hpp>

#include "lc_client/eng_graphics/texture.h"



struct Outline {
	glm::vec3 color;
	float width;

	Outline(glm::vec3 color, float width) : color(color), width(width) {}
};

struct Water {

};

struct Transparent {

};

struct PrimitiveLine {
	glm::vec3 startPoint;
	glm::vec3 endPoint;
	glm::vec3 color;

	PrimitiveLine(glm::vec3 startPoint, glm::vec3 endPoint, glm::vec3 color)
		: startPoint(startPoint),
		  endPoint(endPoint), color(color) {}
};

struct PrimitiveCube {
	glm::vec3 color;

	PrimitiveCube(glm::vec3 color) : color(color){}
};

struct ShaderRequest {
	std::string packName;
	std::string vertexShaderName;
	std::string fragmentShaderName;


	ShaderRequest(
		std::string packName, std::string vertexShaderName, std::string fragmentShaderName)
		: packName(packName),
		  vertexShaderName(vertexShaderName),
		  fragmentShaderName(fragmentShaderName)
	{}
	ShaderRequest(const ShaderRequest&) = default;
};


struct Shader {
	entt::entity* shader;

    std::unordered_map<std::string, glm::vec4> vectorUniforms;
	std::unordered_map<std::string, float> floatUniforms;

	Shader() = default;
	Shader(entt::entity* shader)
		: shader(shader),
    vectorUniforms(std::unordered_map<std::string, glm::vec4>()),
    floatUniforms(std::unordered_map<std::string, float>()){}
	Shader(const Shader&) = default;
};

struct ShaderGl {
	unsigned int shaderProgram;

	ShaderGl() = default;
	ShaderGl(int shaderProgram) : shaderProgram(shaderProgram){};
	ShaderGl(const ShaderGl&) = default;
};

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoords;

	Vertex() = default;
};

struct Mesh {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Mesh() = default;
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, entt::entity& material)
		: vertices(std::move(vertices)),
		  indices(std::move(indices)){};
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, entt::entity& material, int vaoId)
		: vertices(vertices),
		  indices(indices){};
	Mesh(const Mesh& mesh) : vertices(mesh.vertices), indices(mesh.indices){};
};

struct VaoGl {
	unsigned int vaoId;

	VaoGl() = default;
	VaoGl(const int vaoId) : vaoId(vaoId){};
	VaoGl(const VaoGl&) = default;
};

struct MaterialLoadRequest {};

struct MaterialUnloadRequest {};

struct MaterialMR {
	Texture* colorTexture;
	Texture* normalMap;
	Texture* aoTexture;
	Texture* metallicTexture;

	MaterialMR() = default;
	MaterialMR(Shader shader, Texture* colorTexture, Texture* normalMap, Texture* aoTexture, Texture* metallicTexture)
		: colorTexture(colorTexture),
		  normalMap(normalMap),
		  aoTexture(aoTexture),
		  metallicTexture(metallicTexture){};
	MaterialMR(const MaterialMR&) = default;
};

struct MaterialSG {
	Texture* diffuseTexture;
	Texture* specularTexture;
	Texture* glossinessTexture;
	Texture* normalMap;
	Texture* aoTexture;

	MaterialSG() = default;
	MaterialSG(Shader shader, Texture* diffuseTexture, Texture* specularTexture, Texture* glossinessTexture,
		Texture* normalMap, Texture* aoTexture)
		: diffuseTexture(diffuseTexture),
		  specularTexture(specularTexture),
		  glossinessTexture(glossinessTexture),
		  normalMap(normalMap),
		  aoTexture(aoTexture){};
	MaterialSG(const MaterialSG&) = default;
};
