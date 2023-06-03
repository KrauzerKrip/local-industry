#include "lc_client/tier1/openGL/gl_texture_manager.h"

#include <iostream>

#include "lc_client/eng_graphics/openGL/gl_texture.h"


TextureManagerGl::TextureManagerGl(eng::IResource* pResource) : TextureManager(pResource){}

Texture* TextureManagerGl::loadTexture(std::string path) {
	std::shared_ptr<eng::Image> image;

	const std::vector<unsigned char>& buffer = m_pResource->getFileResource(path + FILE_FORMAT);

	image = std::make_shared<eng::Image>(buffer);

	Texture* pTexture = new TextureGL(image); // TODO

	m_textureMap.emplace(path, pTexture);


	std::cout << "Texture '" << path << "' loaded." << std::endl;
	
	return pTexture;
}
