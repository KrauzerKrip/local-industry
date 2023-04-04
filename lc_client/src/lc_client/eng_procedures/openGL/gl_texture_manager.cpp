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

		Texture* pTexture = nullptr;
		
		try {
			pTexture = loadTexture(path);
		}
		catch (ResourceFileNotFoundException& exception) {
			std::cerr << exception.what() << std::endl;
			pTexture = loadTexture("dev/textures/eng_texture_not_found/color");
		}
		catch (FileTooLargeException) {
			throw FileTooLargeException("Image is too large to load it: " + path);
		}
		catch (ImageLoadFailureException& exception) {
			std::cerr << "Failed to load texture: " << path << ": " << exception.what() << std::endl;
			pTexture = loadTexture("dev/textures/eng_texture_not_found/color");
		}

		if (pTexture == nullptr) {
			std::cerr << "TextureManagerGL: pTexture is nullptt. Path given: " << path << std::endl;
			throw std::runtime_error("TextureManagerGL: pTexture is nullptt. Path given: " + path);
		}

		return pTexture;
		
	}
}

Texture* TextureManager::loadTexture(std::string path)	{ 

	std::vector<unsigned char> buffer;
	std::shared_ptr<eng::Image> image;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
	buffer = m_pResource->getFileResource(path + FILE_FORMAT); 

	image = std::make_shared<eng::Image>(buffer);

	Texture* pTexture = new TextureGL(image); // TODO

	m_textureMap.emplace(path, pTexture);


	std::cout << "Texture '" << path << "' loaded." << std::endl;

	return pTexture;
}

const std::string TextureManager::FILE_FORMAT = ".png";
