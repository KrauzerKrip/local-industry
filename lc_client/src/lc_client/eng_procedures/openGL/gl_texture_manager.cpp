#include "gl_texture_manager.h"

#include <iostream>
#include <stdexcept>
#include <memory>

#include "lc_client/eng_graphics/openGL/gl_texture.h"
#include "lc_client/util/image.h"
#include "lc_client/exceptions/io_exceptions.h"


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

	std::vector<unsigned char> buffer;

	try {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
		buffer = m_pResource->getFileResource(path + FILE_FORMAT); 
	}
	catch (ResourceFileNotFoundException& exception) {
		std::cerr << exception.what() << std::endl;
		buffer = m_pResource->getFileResource("dev/textures/texture_not_found/color" + FILE_FORMAT);
	}  

	std::shared_ptr<eng::Image> image;

	try {
		image = std::make_shared<eng::Image>(buffer);
	}
	catch (FileTooLargeException) {
		throw FileTooLargeException("Image is too large to load it: " + path);
	}
	catch (ImageLoadFailureException &exception) {
		std::cerr << "Failed to load texture: " << path << ": " << exception.what() << std::endl;
		buffer = m_pResource->getFileResource("dev/textures/texture_not_found/color" + FILE_FORMAT);
		image = std::make_shared<eng::Image>(buffer);
	}

	Texture* pTexture = new TextureGL(image); // TODO

	m_textureMap.emplace(path, pTexture);

	std::cout << "Texture '" << path << "' loaded." << std::endl;

	return pTexture;
}

const std::string TextureManager::FILE_FORMAT = ".png";
