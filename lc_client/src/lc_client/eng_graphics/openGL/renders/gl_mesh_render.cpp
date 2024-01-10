#include "gl_mesh_render.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_graphics/texture.h"
#include "lc_client/eng_model/entt/components.h"
#include "lc_client/eng_lighting/entt/components.h"
#include "lc_client/eng_cubemaps/entt/components.h"
#include "lc_client/eng_graphics/openGL/gl_shader_uniform.h"



void eng::renderMesh(entt::entity meshEntity, entt::registry* pUtilRegistry) {
	Mesh& mesh = pUtilRegistry->get<Mesh>(meshEntity);
	int vao = pUtilRegistry->get<VaoGl>(meshEntity).vaoId;
	MaterialSG& materialSG = pUtilRegistry->get<MaterialSG>(meshEntity);
	Texture* aoTexture = materialSG.aoTexture;
	Texture* diffuseTexture = materialSG.diffuseTexture;
	Texture* normalMap = materialSG.normalMap;
	Texture* specularMap = materialSG.specularTexture;
	aoTexture->bind();
	diffuseTexture->bind();
	normalMap->bind();
	specularMap->bind();
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, (GLsizei)mesh.indices.size(), GL_UNSIGNED_INT, 0);
}


void eng::setMatrices(unsigned int shaderProgram, glm::mat4& model, glm::mat4& view, glm::mat4 projection) {
	glm::mat4 normal = model;
	glm::inverse(normal);
	glm::transpose(normal);

	// glm::mat4 modelView = view * model;

	unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
	unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
	unsigned int projLoc = glGetUniformLocation(shaderProgram, "projection");
	unsigned int normalMatrixLoc = glGetUniformLocation(shaderProgram, "normalMatrix");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normal));
}

void eng::transform(glm::mat4& model, Transform& transform) {
	model = glm::translate(model, transform.position);
	model *= glm::mat4_cast(transform.rotation);
	model = glm::scale(model, transform.scale);
}

void eng::setMaterialSg(unsigned int shaderProgram) {
	setUniform(shaderProgram, "material.diffuse", TextureType::DIFFUSE);
	setUniform(shaderProgram, "material.normal", TextureType::NORMAL);
	setUniform(shaderProgram, "material.specular", TextureType::SPECULAR);
	setUniform(shaderProgram, "material.shininess", 32.0f);
}
