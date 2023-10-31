#include "gl_texture_cubemap.h"

#include <glad/glad.h>


TextureCubemapGl::TextureCubemapGl(std::shared_ptr<CubemapMaterial> material) { m_material = material; }

void TextureCubemapGl::load() {
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);

	auto material = m_material.get();

	auto& face = material->right;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, face.getWidth(), face.getHeight(), 0, GL_RGB,
		GL_UNSIGNED_BYTE, face.getData());
	auto& face = material->left;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, face.getWidth(), face.getHeight(), 0, GL_RGB,
		GL_UNSIGNED_BYTE, face.getData());
	auto& face = material->top;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, face.getWidth(), face.getHeight(), 0, GL_RGB,
		GL_UNSIGNED_BYTE, face.getData());
	auto& face = material->bottom;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, face.getWidth(), face.getHeight(), 0, GL_RGB,
		GL_UNSIGNED_BYTE, face.getData());
	auto& face = material->back;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, face.getWidth(), face.getHeight(), 0, GL_RGB,
		GL_UNSIGNED_BYTE, face.getData());
	auto& face = material->front;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, face.getWidth(), face.getHeight(), 0, GL_RGB,
		GL_UNSIGNED_BYTE, face.getData());

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void TextureCubemapGl::unload() {}

void TextureCubemapGl::bind() {}
