#include "gl_render.h"

#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_graphics/texture.h"
#include "lc_client/eng_model/entt/components.h"

RenderGL::RenderGL(IWindow* pWindow, Camera* pCamera) {
	m_pWindow = pWindow; //mb remove it
	m_pCamera = pCamera;
}

RenderGL::~RenderGL() {

}

void RenderGL::init() {
	glEnable(GL_DEPTH_TEST);
}

void RenderGL::render() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float aspectRatio = (float)m_pWindow->getAspectRatio()[0] / (float)m_pWindow->getAspectRatio()[1];
	glm::mat4 projection = glm::perspective(glm::radians(m_pWindow->getFov()), aspectRatio, 0.1f, 100.0f);
	glm::mat4 view = m_pCamera->getViewMatrix(); // glm::mat4(1.0f);

	auto materialEntitiesGroup = m_pSceneRegistry->group<Model, Transform, ShaderGl>(); // TODO

	for (entt::entity entity : materialEntitiesGroup) {

		Model& model = materialEntitiesGroup.get<Model>(entity);
		Transform& transform = materialEntitiesGroup.get<Transform>(entity);

		std::vector<entt::entity>& meshes = model.meshes;

		unsigned int shaderProgram = materialEntitiesGroup.get<ShaderGl>(entity).shaderProgram;

		glUseProgram(shaderProgram);

		glUniform1i(glGetUniformLocation(shaderProgram, "textureSamplerColor"), 4);
		glUniform1i(glGetUniformLocation(shaderProgram, "textureSamplerNormal"), 1);

		glm::mat4 modelMatrix = glm::mat4(1.0f);
		RenderGL::transform(modelMatrix, transform);

		//glm::mat4 modelView = view * model;

		unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
		unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
		unsigned int projLoc = glGetUniformLocation(shaderProgram, "projection");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		for (entt::entity& meshEntity : meshes) {
			Mesh& mesh = m_pUtilRegistry->get<Mesh>(meshEntity);
			int vao = mesh.vaoId;
			MaterialSG& materialSG = m_pUtilRegistry->get<MaterialSG>(meshEntity);

			Texture* aoTexture = materialSG.aoTexture;
			Texture* diffuseTexture = materialSG.diffuseTexture;
			Texture* normalMap = materialSG.normalMap;

			aoTexture->bind();
			diffuseTexture->bind();
			normalMap->bind();

			glBindVertexArray(vao);
			glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
		}



	}

}

void RenderGL::clear() {

}

void RenderGL::cleanUp() {

}

void RenderGL::setRegistries(entt::registry* pMapRegistry, entt::registry* pSceneRegistry, entt::registry* pUtilRegistry) {
	m_pMapRegistry = pMapRegistry;
	m_pSceneRegistry = pSceneRegistry;
	m_pUtilRegistry = pUtilRegistry;
}

void RenderGL::transform(glm::mat4& model, Transform& transform) {
	model = glm::translate(model, transform.position);
	model = glm::rotate(model, glm::radians(-55.0f), transform.rotation);
	model = glm::scale(model, transform.scale);
}
