#pragma once

#include "../texture.h"

class TextureGL : Texture {
	void load();
	void unload();
	void bind();
};
