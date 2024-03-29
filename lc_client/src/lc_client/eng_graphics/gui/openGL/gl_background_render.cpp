#include "gl_background_render.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <iostream>
#include "lc_client/eng_graphics/openGL/gl_shader_uniform.h"


BackgroundRenderGl::BackgroundRenderGl(
	IConsole* pConsole, ShaderLoaderGl* pShaderWork, TextureManager* pTextureManager, FramebufferController* pFramebufferController)
	: BackgroundRender(m_pConsole) {
	m_pTextureManager = pTextureManager;
	m_pFramebufferController = pFramebufferController;

	m_colorShader = pShaderWork->createShaderProgram("gui_quad", "gui_quad");
	m_imageShader = pShaderWork->createShaderProgram("gui_quad", "gui_image_quad");
	m_blurShader = pShaderWork->createShaderProgram("gui_quad", "gui_blur_quad");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_projection = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f);

	glGenVertexArrays(1, &m_vao); 
	glGenBuffers(1, &m_vbo);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}



void BackgroundRenderGl::renderColor(ColorQuad colorQuad) {
	unsigned int shader;
	if (colorQuad.blurIntensity == 0) {
		shader = m_colorShader;
	}
	else {
		shader = m_blurShader;
	}

	glUseProgram(shader);
	unsigned int projLoc = glGetUniformLocation(shader, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(m_projection));
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(m_vao);

	glm::vec2 bottomLeft = colorQuad.vertices.bottomLeft;
	glm::vec2 topLeft = colorQuad.vertices.topLeft;
	glm::vec2 topRight = colorQuad.vertices.topRight;
	glm::vec2 bottomRight = colorQuad.vertices.bottomRight;

	float vertices[6][4] = {{topLeft.x, topLeft.y, 0.0f, 1.0f}, {bottomLeft.x, bottomLeft.y, 0.0f, 0.0f},
		{bottomRight.x, bottomRight.y, 1.0f, 0.0f},

		{topLeft.x, topLeft.y, 0.0f, 1.0f}, {bottomRight.x, bottomRight.y, 1.0f, 0.0f},
		{topRight.x, topRight.y, 1.0f, 1.0f}};

	setUniform(shader, "zOffset", colorQuad.zOffset);
	setUniform(shader, "quadColor", colorQuad.color);
	if (colorQuad.blurIntensity != 0) {
		m_pFramebufferController->getBlurFramebuffer()->bind();
		m_pFramebufferController->getFramebuffer()->bindTexture();

		setUniform(shader, "sigma", colorQuad.blurIntensity);
		setUniform(shader, "direction", glm::vec2(1.0f, 0.0f));
		setUniform(shader, "screenTexture", TextureType::FRAMEBUFFER);
		setUniform(shader, "screenTextureSize", glm::vec2(1920, 1057));
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// render quad
	glDrawArrays(GL_TRIANGLES, 0, 6);

	if (colorQuad.blurIntensity != 0) {
		m_pFramebufferController->getFramebuffer()->bind();
		m_pFramebufferController->getBlurFramebuffer()->bindTexture();
		setUniform(shader, "direction", glm::vec2(0.0f, 1.0f));
		setUniform(shader, "screenTexture", TextureType::BLUR_FRAMEBUFFER);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void BackgroundRenderGl::renderImage(ImageQuad imageQuad) {
	glUseProgram(m_imageShader);
	unsigned int projLoc = glGetUniformLocation(m_imageShader, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(m_projection));
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(m_vao);

	glm::vec2 bottomLeft = imageQuad.vertices.bottomLeft;
	glm::vec2 topLeft = imageQuad.vertices.topLeft;
	glm::vec2 topRight = imageQuad.vertices.topRight;
	glm::vec2 bottomRight = imageQuad.vertices.bottomRight;

	//float vertices[6][4] = {
	//    {topLeft.x, topLeft.y, 0.0f, 1.0f},
	//    {bottomLeft.x, bottomLeft.y, 0.0f, 0.0f},
	//	{bottomRight.x, bottomRight.y, 1.0f, 0.0f},
	//	{topLeft.x, topLeft.y, 0.0f, 1.0f},
	//    {bottomRight.x, bottomRight.y, 1.0f, 0.0f},
	//	{topRight.x, topRight.y, 1.0f, 1.0f}};

  //  float vertices[6][4] = {
  //      {topLeft.x, topLeft.y, 1.0f, 0.0f},
	 //   {bottomLeft.x, bottomLeft.y, 1.0f, 1.0f},
		//{bottomRight.x, bottomRight.y, 0.0f, 1.0f},
		//{topLeft.x, topLeft.y, 1.0f, 0.0f},
		//{bottomRight.x, bottomRight.y, 0.0f, 1.0f},
		//{topRight.x, topRight.y, 0.0f, 0.0f}};

    float vertices[6][4] = {
        {topLeft.x, topLeft.y, 0.0f, 0.0f},
	    {bottomLeft.x, bottomLeft.y, 0.0f, 1.0f},
		{bottomRight.x, bottomRight.y, 1.0f, 1.0f},
		{topLeft.x, topLeft.y, 0.0f, 0.0f},
		{bottomRight.x, bottomRight.y, 1.0f, 1.0f},
		{topRight.x, topRight.y, 1.0f, 0.0f}};

	setUniform(m_imageShader, "zOffset", imageQuad.zOffset);
	setUniform(m_imageShader, "image", TextureType::NORMAL);
	imageQuad.pTexture->bind();

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// render quad
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture* BackgroundRenderGl::getTexture(std::string path) { return m_pTextureManager->getTexture(path); }