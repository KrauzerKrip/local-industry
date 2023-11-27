#include "gl_render_background.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <iostream>
#include "lc_client/eng_graphics/openGL/gl_shader_uniform.h"
#include "lc_client/eng_graphics/openGL/gl_shader_uniform.h"


RenderBackgroundGl::RenderBackgroundGl(IConsole* pConsole, ShaderWorkGl* pShaderWork) : RenderBackground(m_pConsole) {
	pShaderWork->createShaderProgram("quad", "quad");

	m_shader = pShaderWork->createShaderProgram("quad", "quad");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_projection = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f);

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

void RenderBackgroundGl::renderColor(ColorQuad colorQuad) {
	glUseProgram(m_shader);
	unsigned int projLoc = glGetUniformLocation(m_shader, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(m_projection));
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(m_vao);

	glm::vec2 bottomLeft = colorQuad.absolutePosition;
	glm::vec2 topLeft = glm::vec2(colorQuad.absolutePosition.x, colorQuad.absolutePosition.y + colorQuad.size.y);
	glm::vec2 topRight = glm::vec2(colorQuad.absolutePosition.x + colorQuad.size.x, colorQuad.absolutePosition.y + colorQuad.size.y);
	glm::vec2 bottomRight = glm::vec2(colorQuad.absolutePosition.x + colorQuad.size.x, colorQuad.absolutePosition.y);

	float vertices[6][4] = {{topLeft.x, topLeft.y, 0.0f, 1.0f}, {bottomLeft.x, bottomLeft.y, 0.0f, 0.0f},
		{bottomRight.x, bottomRight.y, 1.0f, 0.0f},

		{topLeft.x, topLeft.y, 0.0f, 1.0f}, {bottomRight.x, bottomRight.y, 1.0f, 0.0f},
		{topRight.x, topRight.y, 1.0f, 1.0f}};

	float zOffset = (float)colorQuad.layer / 100; // should not be bigger than 2

	setUniform(m_shader, "zOffset", zOffset);
	setUniform(m_shader, "quadColor", colorQuad.background.getColor());

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// render quad
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void RenderBackgroundGl::renderImage(ImageQuad colorQuad) {}
