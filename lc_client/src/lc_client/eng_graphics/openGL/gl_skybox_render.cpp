#include "gl_skybox_render.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "lc_client/exceptions/graphics_exceptions.h"
#include "lc_client/eng_graphics/texture.h"


SkyboxRenderGl::SkyboxRenderGl(CubemapMaterial* material, ShaderWorkGl* pShaderWork) {
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);

	CubemapMaterial* pMat = material;

	int imageFormat;

	if (pMat->right.getChannelsNumber() > 3 || pMat->left.getChannelsNumber() > 3 || pMat->top.getChannelsNumber() > 3||
		pMat->bottom.getChannelsNumber() > 3|| pMat->back.getChannelsNumber() > 3|| pMat->front.getChannelsNumber() > 3){
		imageFormat = GL_RGBA;
		//throw TextureLoadException("There are more than 3 color channels. For a skybox texture the appropriate format is RGB.");
	} else {
		imageFormat = GL_RGB;
	}

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, imageFormat, pMat->right.getWidth(), pMat->right.getHeight(), 0, imageFormat,
		GL_UNSIGNED_BYTE, pMat->right.getData());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, imageFormat, pMat->left.getWidth(), pMat->left.getHeight(), 0, imageFormat,
		GL_UNSIGNED_BYTE, pMat->left.getData());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, imageFormat, pMat->top.getWidth(), pMat->top.getHeight(), 0, imageFormat,
		GL_UNSIGNED_BYTE, pMat->top.getData());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, imageFormat, pMat->bottom.getWidth(), pMat->bottom.getHeight(), 0,
		imageFormat, GL_UNSIGNED_BYTE, pMat->bottom.getData());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, imageFormat, pMat->back.getWidth(), pMat->back.getHeight(), 0, imageFormat,
		GL_UNSIGNED_BYTE, pMat->back.getData());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, imageFormat, pMat->front.getWidth(), pMat->front.getHeight(), 0,
		imageFormat, GL_UNSIGNED_BYTE, pMat->front.getData());

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	float skyboxVertices[] = {// positions
		-1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f,
		-1.0f,

		-1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f,

		1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f,
		-1.0f,

		-1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
		1.0f,

		-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f,
		-1.0f,

		-1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f};

	unsigned int vbo;
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	m_shader = pShaderWork->createShaderProgram("skybox", "skybox");
}

void SkyboxRenderGl::render(glm::mat4& projection, glm::mat4& view) {
	glDepthMask(GL_FALSE);
	glUseProgram(m_shader);

	unsigned int viewLoc = glGetUniformLocation(m_shader, "view");
	unsigned int projLoc = glGetUniformLocation(m_shader, "projection");

	glm::mat4 skyboxView = glm::mat4(glm::mat3(view));

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(skyboxView));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(m_vao);
	glActiveTexture(GL_TEXTURE0 + TextureType::SKYBOX);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthMask(GL_TRUE);
}

void SkyboxRenderGl::bindTexture() { glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture); }