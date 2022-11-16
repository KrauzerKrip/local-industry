#include "gl_texture.h"

#include <glad/glad.h>
#include <vector>


TextureGL::TextureGL(std::shared_ptr<eng::Image> image) {
	m_image = image;

	glGenTextures(1, &m_textureGl);
}

void TextureGL::load() {
	glBindTexture(GL_TEXTURE_2D, m_textureGl);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_FALSE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_image->getWidth(), m_image->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_image->getData());
	glGenerateMipmap(GL_TEXTURE_2D);
}

void TextureGL::unload() {
}

void TextureGL::bind() {
	glBindTexture(GL_TEXTURE_2D, m_textureGl);
}

