#include "gl_texture_manager.h"

#include <iostream>
#include <stdexcept>
#include <memory>

#include "lc_client/eng_graphics/openGL/gl_texture.h"
#include "lc_client/util/image.h"

TextureManager::TextureManager(eng::IResource* pResource) {
	m_pResource = pResource;
}

Texture* TextureManager::getTexture(std::string path) {
	try {
		return m_textureMap.at(path);
	}
	catch (std::out_of_range) {
		std::cout << "Texture '" << path << "' not found in cache, will try to load." << std::endl;
		return loadTexture(path);
	}
}

Texture* TextureManager::loadTexture(std::string path)	{
	auto buffer = m_pResource->getFileResource(path + FILE_FORMAT);
	std::shared_ptr<eng::Image> image = std::make_shared<eng::Image>(buffer);
	Texture* pTexture = new TextureGL(image);

	pTexture->load();

	m_textureMap.emplace(path, pTexture);

	return pTexture;
}

const std::string TextureManager::FILE_FORMAT = ".png";
