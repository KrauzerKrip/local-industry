#pragma once

#include "lc_client/tier1/texture_manager.h"

class TextureManagerGl : public TextureManager {
public:
	TextureManagerGl(eng::IResource* pResource);

private:
	Texture* loadTexture(std::string path);
};
