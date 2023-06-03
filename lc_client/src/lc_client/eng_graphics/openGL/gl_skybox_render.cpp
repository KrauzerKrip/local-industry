#include "gl_skybox_render.h"

#include <glad/glad.h>

#include "lc_client/exceptions/graphics_exceptions.h"


SkyboxRenderGl::SkyboxRenderGl(CubemapMaterial* material, ShaderWorkGl* pShaderWork) {
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);

	CubemapMaterial* pMat = material;

	if (pMat->right.getChannelsNumber() > 3 || pMat->left.getChannelsNumber() > 3 || pMat->top.getChannelsNumber() > 3||
		pMat->bottom.getChannelsNumber() > 3|| pMat->back.getChannelsNumber() > 3|| pMat->front.getChannelsNumber() > 3){
		throw TextureLoadException("There are more than 3 color channels. For a skybox texture the appropriate format is RGB.");
	}

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, pMat->right.getWidth(), pMat->right.getHeight(), 0, GL_RGB,
		GL_UNSIGNED_BYTE, pMat->right.getData());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, pMat->left.getWidth(), pMat->left.getHeight(), 0, GL_RGB,
		GL_UNSIGNED_BYTE, pMat->left.getData());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, pMat->top.getWidth(), pMat->top.getHeight(), 0, GL_RGB,
		GL_UNSIGNED_BYTE, pMat->top.getData());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, pMat->bottom.getWidth(), pMat->bottom.getHeight(), 0,
		GL_RGB, GL_UNSIGNED_BYTE, pMat->bottom.getData());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, pMat->back.getWidth(), pMat->back.getHeight(), 0, GL_RGB,
		GL_UNSIGNED_BYTE, pMat->back.getData());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, pMat->front.getWidth(), pMat->front.getHeight(), 0,
		GL_RGB, GL_UNSIGNED_BYTE, pMat->front.getData());

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

void SkyboxRenderGl::render() {
	glDepthMask(GL_FALSE);
	glUseProgram(m_shader);
	glBindVertexArray(m_vao);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthMask(GL_TRUE);
}
