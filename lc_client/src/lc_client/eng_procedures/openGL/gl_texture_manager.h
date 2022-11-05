#pragma once

#include <unordered_map>

#include "lc_client/eng_graphics/texture.h"


class TextureManager {
public:
	Texture& getTexture(std::string name);

private: 
	Texture& loadTexture(std::string name);

	std::unordered_map<std::string, Texture&> m_textureMap;
};