#pragma once

#include <unordered_map>

#include "lc_client/eng_graphics/texture.h"
#include "lc_client/util/i_eng_resource.h"


class TextureManager {
public:
	TextureManager(eng::IResource* pResource);

	Texture* getTexture(std::string path);

protected: 
	virtual Texture* loadTexture(std::string path) = 0;

	std::unordered_map<std::string, Texture*> m_textureMap;
	
	eng::IResource* m_pResource;

	const static std::string FILE_FORMAT;
};