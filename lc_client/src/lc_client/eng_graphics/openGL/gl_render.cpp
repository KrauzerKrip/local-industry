#include "gl_render.h"
#include "gl_render.h"

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "lc_client/eng_graphics/entt/components.h"

RenderGL::RenderGL(IWindow* pWindow) {
	m_pWindow = pWindow; //mb remove it
}

RenderGL::~RenderGL() {

}

void RenderGL::init() {

}

void RenderGL::render() {

	auto materialEntitiesGroup = m_pSceneRegistry->group<MaterialGl, Mesh>();

	for (entt::entity entity : materialEntitiesGroup) {

		MaterialGl& materialGl = materialEntitiesGroup.get<MaterialGl>(entity);
		int shaderProgram = materialGl.shaderProgram;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f, 
			0.0f, 0.5f, 0.0f
		};

		unsigned int vbo;
		glGenBuffers(1, &vbo);

		unsigned int vao;
		glGenVertexArrays(1, &vao);

		// 1. bind Vertex Array Object
		glBindVertexArray(vao);
		// 2. copy our vertices array in a buffer for OpenGL to use
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// 3. then set our vertex attributes pointers
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
			(void*)0);
		glEnableVertexAttribArray(0);
		// ..:: Drawing code (in render loop) :: ..
		// 4. draw the object
		glUseProgram(shaderProgram);
		glBindVertexArray(vao);

		glDrawArrays(GL_TRIANGLES, 0, 3);

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
