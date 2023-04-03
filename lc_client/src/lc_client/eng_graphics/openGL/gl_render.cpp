#include "gl_render.h"

#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_graphics/texture.h"

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

	auto materialEntitiesGroup = m_pSceneRegistry->group<MaterialSG, ShaderGl, VaoGl, Transform>(); // TODO

	for (entt::entity entity : materialEntitiesGroup) {

		MaterialSG& materialSG = materialEntitiesGroup.get<MaterialSG>(entity);
		VaoGl& vaoGl = materialEntitiesGroup.get<VaoGl>(entity);
		Transform& transform = materialEntitiesGroup.get<Transform>(entity);
		entt::entity* shader = materialSG.shader.shader; 
		unsigned int shaderProgram = materialEntitiesGroup.get<ShaderGl>(*shader).shaderProgram; // ERROR

		int vaoId = vaoGl.vaoId;

		Texture* aoTexture = materialSG.aoTexture;
		Texture* diffuseTexture = materialSG.diffuseTexture;
		Texture* normalMap = materialSG.normalMap;

		glUseProgram(shaderProgram);

		glUniform1i(glGetUniformLocation(shaderProgram, "textureSamplerColor"), 0);
		glUniform1i(glGetUniformLocation(shaderProgram, "textureSamplerNormal"), 1);

		glm::mat4 model = glm::mat4(1.0f);
		RenderGL::transform(model, transform);

		//glm::mat4 modelView = view * model;

		unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
		unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
		unsigned int projLoc = glGetUniformLocation(shaderProgram, "projection");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


		aoTexture->bind();
		diffuseTexture->bind();
		normalMap->bind();

		glBindVertexArray(vaoId);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

}

void RenderGL::clear() {

}

void RenderGL::cleanUp() {

}

void RenderGL::setRegistries(entt::registry* mapRegistry, entt::registry* sceneRegistry) {
	m_pMapRegistry = mapRegistry;
	m_pSceneRegistry = sceneRegistry;
}

void RenderGL::transform(glm::mat4& model, Transform& transform) {
	model = glm::translate(model, transform.position);
	model = glm::rotate(model, glm::radians(-55.0f), transform.rotation);
	model = glm::scale(model, transform.scale);
}
