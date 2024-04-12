#include "texture_manager.h"

#include <iostream>
#include <stdexcept>
#include <memory>

#include "lc_client/util/image.h"
#include "lc_client/exceptions/io_exceptions.h"
#include "lc_client/tier0/tier0.h"


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
			Tier0::getIConsole()->warn(exception.what());
			pTexture = loadTexture("dev/textures/eng_texture_not_found/color");
		}
		catch (FileTooLargeException) {
			throw FileTooLargeException("Image is too large to load it: " + path);
		}
		catch (ImageLoadFailureException& exception) {
			std::cerr << "Failed to load texture: " << path << ": " << exception.what() << std::endl;
			Tier0::getIConsole()->warn("Failed to load texture: " + path + ": " + exception.what());
			pTexture = loadTexture("dev/textures/eng_texture_not_found/color");
		}

		if (pTexture == nullptr) {
			std::string str = "TextureManagerGL: pTexture is nullptr. Path given: " + path;
			_ASSERT(str.c_str());
		}

		return pTexture;
		
	}
}

void TextureManager::reload() {
	for (auto [path, pTexture] : m_textureMap) {
		try {
			//delete pTexture;
			pTexture = loadTexture(path);
		}
		catch (ResourceFileNotFoundException& exception) {
			std::cerr << exception.what() << std::endl;
			Tier0::getIConsole()->warn(exception.what());
			pTexture = loadTexture("dev/textures/eng_texture_not_found/color");
		}
		catch (FileTooLargeException) {
			std::cerr << ("Image is too large to load it: " + path) << std::endl;
		}
		catch (ImageLoadFailureException& exception) {
			std::cerr << "Failed to load texture: " << path << ": " << exception.what() << std::endl;
			Tier0::getIConsole()->warn("Failed to load texture: " + path + ": " + exception.what());
			pTexture = loadTexture("dev/textures/eng_texture_not_found/color");
		}

		if (pTexture == nullptr) {
			std::string str = "TextureManagerGL: pTexture is nullptt. Path given: " + path;
			_ASSERT(str.c_str());
		}
	}
}


const std::string TextureManager::FILE_FORMAT = ".png";
