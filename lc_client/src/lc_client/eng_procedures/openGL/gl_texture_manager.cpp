#include "gl_texture_manager.h"

#include <iostream>
#include <stdexcept>
#include <memory>

#include "lc_client/eng_graphics/openGL/gl_texture.h"
#include "lc_client/util/image.h"

TextureManager::TextureManager(eng::IResource* pResource) {
	m_pResource = pResource;
}

Texture& TextureManager::getTexture(std::string name) {
	try {
		return m_textureMap.at(name);
	}
	catch (std::out_of_range) {
		std::cout << "Texture '" << name << "' not found in cache, will try to load." << std::endl;
		return loadTexture(name);
	}
}

Texture& TextureManager::loadTexture(std::string name)	{
	auto buffer = m_pResource->getFileResource(name);
	std::shared_ptr<eng::Image> image = std::make_shared<eng::Image>(buffer);
	TextureGL textureGL(image);
	Texture& texture = textureGL;

	texture.load();

	m_textureMap.emplace(name, texture);

	return texture;
}
