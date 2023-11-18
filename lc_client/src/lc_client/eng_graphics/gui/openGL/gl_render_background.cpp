#include "gl_render_background.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <iostream>
#include "lc_client/eng_graphics/openGL/gl_shader_uniform.h"


RenderBackgroundGl::RenderBackgroundGl(IConsole* pConsole, ShaderGl shader) : RenderBackground(m_pConsole) {
	m_shader = shader.shaderProgram;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_projection = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f);

	//float quadVertices[] = {// positions     // colors
	//	-0.05f, 0.05f, 1.0f, 
	//	0.0f, 0.0f, 0.05f,
	//	-0.05f, 0.0f, 1.0f,
	//	0.0f, -0.05f, -0.05f,
	//	0.0f, 0.0f, 1.0f,

	//	-0.05f, 0.05f, 
	//	
	//	1.0f, 0.0f, 0.0f, 0.05f, -0.05f, 0.0f, 1.0f, 0.0f, 0.05f, 0.05f, 0.0f, 1.0f, 1.0f}; 

float quadVertices[] = {
		0.5f, 0.5f, 0.0f,	// top right
		0.5f, -0.5f, 0.0f,	// bottom right
		-0.5f, -0.5f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f	// top left
	};

unsigned int indices[] = {
		// note that we start from 0!
		0, 1, 3, // first triangle
		1, 2, 3	 // second triangle
	};

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	//unsigned int ebo;
	//glGenBuffers(1, &ebo);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//glBindVertexArray(VAO);
	//// 2. copy our vertices array in a vertex buffer for OpenGL to use
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//// 3. copy our index array in a element buffer for OpenGL to use
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//// 4. then set the vertex attributes pointers
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
	//// ..:: Drawing code (in render loop) :: ..
	//	glUseProgram(shaderProgram);
	//glBindVertexArray(VAO);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0) glBindVertexArray(0);
}

void RenderBackgroundGl::addToQueue(Background& background, std::array<glm::vec2, 4> vertices) { 
	ColorQuad quad(background, vertices);
	m_colorQuads.push(quad);
}

void RenderBackgroundGl::addToQueue(ImageBackground& background, std::array<glm::vec2, 4> vertices) {
	ImageQuad quad(background, vertices);
	m_imageQuads.push(quad);
}

void RenderBackgroundGl::render() {
	while (m_colorQuads.size() != 0) {
		ColorQuad quad = m_colorQuads.front();
		m_colorQuads.pop();

		glm::vec2 bottomLeft = quad.vertices.at(0);
		glm::vec2 topLeft = quad.vertices.at(1);
		glm::vec2 topRight = quad.vertices.at(2);
		glm::vec2 bottomRight = quad.vertices.at(3);

        float vertices[6][4] = {
            { topLeft.x,     topLeft.y,           0.0f, 1.0f },
            { bottomRight.x, bottomRight.y,       1.0f, 0.0f },
            { bottomLeft.x, bottomLeft.y,         0.0f, 0.0f },
 
            { topLeft.x, topLeft.y,               0.0f, 1.0f},
            { topRight.x, topRight.y,             1.0f, 1.0f },
			{ bottomRight.x, bottomRight.y,       1.0f, 0.0f}
        };
		
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}
