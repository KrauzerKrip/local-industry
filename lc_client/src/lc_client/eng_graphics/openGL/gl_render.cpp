#include "gl_render.h"
#include "gl_render.h"

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

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

	auto materialEntitiesGroup = m_pSceneRegistry->group<MaterialGl, VaoGl>();

	for (entt::entity entity : materialEntitiesGroup) {



		MaterialGl& materialGl = materialEntitiesGroup.get<MaterialGl>(entity);
		VaoGl& vaoGl = materialEntitiesGroup.get<VaoGl>(entity);
		int shaderProgram = materialGl.shaderProgram;
		int vaoId = vaoGl.vaoId;

		Texture* aoTexture = materialGl.aoTexture; // null
		Texture* colorTexture = materialGl.colorTexture;
		Texture* metallicTexture = materialGl.metallicTexture;
		Texture* normalMap = materialGl.normalMap;
		

		glUseProgram(shaderProgram);

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
