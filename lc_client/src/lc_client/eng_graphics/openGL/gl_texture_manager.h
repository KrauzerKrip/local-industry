#pragma once

#include "lc_client/eng_graphics/texture_manager.h"

class TextureManagerGl : public TextureManager {
public:
	TextureManagerGl(eng::IResource* pResource);

private:
	Texture* loadTexture(std::string path);
};
