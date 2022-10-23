#include "gl_render.h"

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

RenderGL::RenderGL(IWindow* pWindow) {
	m_pWindow = pWindow; //mb remove it
}

RenderGL::~RenderGL() {

}

void RenderGL::init() {

}

void RenderGL::render(std::vector<entt::entity>* pGraphicsEntities) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

}

void RenderGL::clear() {

}

void RenderGL::cleanUp() {

}