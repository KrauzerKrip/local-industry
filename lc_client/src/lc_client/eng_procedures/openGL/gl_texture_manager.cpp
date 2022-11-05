#include "gl_texture_manager.h"

#include <iostream>
#include <stdexcept>

#include "lc_client/eng_graphics/openGL/gl_texture.h"

Texture& TextureManager::getTexture(std::string name) {
	try {
		return m_textureMap.at(name);
	}
	catch (std::out_of_range) {
		std::cout << "Texture '" << name << "' not found in cache, will try to load." << std::endl;
	}
}

Texture& TextureManager::loadTexture(std::string name)	{
	
}
