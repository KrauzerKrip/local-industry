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
		0.5f, 0.5f, 0.0f, // top right
		0.5f, -0.5f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f // top left
		};
		unsigned int indices[] = { // note that we start from 0!
		0, 1, 3, // first triangle
		1, 2, 3 // second triangle
		};


		unsigned int vbo;
		glGenBuffers(1, &vbo);

		unsigned int vao;
		glGenVertexArrays(1, &vao);

		unsigned int ebo;
		glGenBuffers(1, &ebo);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
		// 1. bind Vertex Array Object
		glBindVertexArray(vao);
		// 2. copy our vertices array in a vertex buffer for OpenGL to use
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// 3. copy our index array in a element buffer for OpenGL to use
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		
		// 4. then set the vertex attributes pointers
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glUseProgram(shaderProgram);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

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
