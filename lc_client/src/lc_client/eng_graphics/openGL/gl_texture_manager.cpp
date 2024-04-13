#include "gl_texture_manager.h"

#include <iostream>

#include "lc_client/eng_graphics/openGL/gl_texture.h"


TextureManagerGl::TextureManagerGl(eng::IResource* pResource) : TextureManager(pResource){}

Texture* TextureManagerGl::loadTexture(std::string path) {
	eng::Image* pImage;

	const std::vector<unsigned char>& buffer = m_pResource->getFileResource(path + FILE_FORMAT);

	pImage = new eng::Image(buffer);

	Texture* pTexture = new TextureGL(pImage); // TODO

	std::cout << "Texture '" << path << "' loaded." << std::endl;
	
	return pTexture;
}
