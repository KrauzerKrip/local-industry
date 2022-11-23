#include "gl_render.h"

#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_graphics/texture.h"

RenderGL::RenderGL(IWindow* pWindow) {
	m_pWindow = pWindow; //mb remove it
}

RenderGL::~RenderGL() {

}

void RenderGL::init() {

}

void RenderGL::render() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	auto materialEntitiesGroup = m_pSceneRegistry->group<MaterialGl, VaoGl, Transform>();

	for (entt::entity entity : materialEntitiesGroup) {

		MaterialGl& materialGl = materialEntitiesGroup.get<MaterialGl>(entity);
		VaoGl& vaoGl = materialEntitiesGroup.get<VaoGl>(entity);
		Transform& transform = materialEntitiesGroup.get<Transform>(entity);
		int shaderProgram = materialGl.shaderProgram;
		int vaoId = vaoGl.vaoId;

		Texture* aoTexture = materialGl.aoTexture;
		Texture* colorTexture = materialGl.colorTexture;
		Texture* metallicTexture = materialGl.metallicTexture;
		Texture* normalMap = materialGl.normalMap;

		glUseProgram(shaderProgram);

		glUniform1i(glGetUniformLocation(shaderProgram, "textureSamplerColor"), 0);
		glUniform1i(glGetUniformLocation(shaderProgram, "textureSamplerNormal"), 1);

		glm::mat4 transformation = glm::mat4(1.0f);
		RenderGL::transform(transformation, transform);

		unsigned int transformLocation = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformation));

		aoTexture->bind();
		colorTexture->bind();
		metallicTexture->bind();
		normalMap->bind();
  
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, blueValue, 1.0f);

		glBindVertexArray(vaoId);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0);

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

void RenderGL::transform(glm::mat4& transformation, Transform& transform) {
	transformation = glm::rotate(transformation, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	transformation = glm::scale(transformation, glm::vec3(0.5, 0.5, 0.5));
}
