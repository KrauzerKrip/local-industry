#pragma once

#include <unordered_map>

#include "lc_client/eng_graphics/texture.h"
#include "lc_client/util/i_resource.h"

class TextureManager {
public:
	TextureManager(eng::IResource* pResource);

	Texture& getTexture(std::string name);

private: 
	Texture& loadTexture(std::string name);

	std::unordered_map<std::string, Texture&> m_textureMap;
	
	eng::IResource* m_pResource;
};