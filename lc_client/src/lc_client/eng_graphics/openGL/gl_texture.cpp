#include "gl_texture.h"

#include <glad/glad.h>
#include <vector>
#include <stdexcept>
#include <iostream>

#define DEBUG


TextureGL::TextureGL(std::shared_ptr<eng::Image> image) {
	m_image = image;

	glGenTextures(1, &m_textureGl);
}

void TextureGL::load() {

	if (m_textureType == TextureType::NONE) {
		std::cerr << "Texture type is undefined" << std::endl;
		throw std::runtime_error("Texture type is undefined.");
	}

#ifdef DEBUG
	if (m_textureType == TextureType::COLOR) {
		std::cout << "COLOR: " << GL_TEXTURE0 + m_textureType << m_textureType <<std::endl;
	}

	if (m_textureType == TextureType::NORMAL) {
		std::cout << "NORMAL: " << GL_TEXTURE0 + m_textureType << m_textureType << std::endl;
	}

	if (m_textureType == TextureType::AO) {
		std::cout << "AO: " << GL_TEXTURE0 + m_textureType << m_textureType << std::endl;
	}

	if (m_textureType == TextureType::METALLIC) {
		std::cout << "METALLIC: " << GL_TEXTURE0 + m_textureType << m_textureType << std::endl;
	}

	if (m_textureType == TextureType::DIFFUSE) {
		std::cout << "DIFFUSE: " << GL_TEXTURE0 + m_textureType << m_textureType << std::endl;
	}

	if (m_textureType == TextureType::GLOSSINESS) {
		std::cout << "GLOSSINESS: " << GL_TEXTURE0 + m_textureType << m_textureType << std::endl;
	}

	if (m_textureType == TextureType::SPECULAR) {
		std::cout << "SPECULAR: " << GL_TEXTURE0 + m_textureType << m_textureType << std::endl;
	}

#endif

	glActiveTexture(GL_TEXTURE0 + m_textureType);
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
	glActiveTexture(GL_TEXTURE0 + m_textureType);
	glBindTexture(GL_TEXTURE_2D, m_textureGl);
}


void TextureGL::setTextureType(TextureType textureType) {
	m_textureType = textureType;
}
