#include "gl_mesh_loader.h"

#include <glad/glad.h>


void MeshLoaderGl::loadMesh(entt::registry* pUtilRegistry, entt::entity entity) {
	Mesh& mesh = pUtilRegistry->get<Mesh>(entity);

	pUtilRegistry->emplace_or_replace<VaoGl>(entity, VaoGl(createVao(mesh.vertices, mesh.indices)));

	pUtilRegistry->emplace_or_replace<MaterialLoadRequest>(entity);
}

unsigned int MeshLoaderGl::createVao(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
	unsigned int vbo;
	glGenBuffers(1, &vbo);

	unsigned int vao;
	glGenVertexArrays(1, &vao);

	unsigned int ebo;
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));


	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, textureCoords)));

	glBindVertexArray(0);

	return vao;
}
