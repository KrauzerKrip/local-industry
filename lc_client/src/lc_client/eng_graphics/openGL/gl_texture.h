#pragma once
#include "lc_client/eng_graphics/texture.h"

#include "lc_client/util/image.h"


class TextureGL : public Texture {
public:
	TextureGL(std::shared_ptr<eng::Image>);

	void load();
	void unload();
	void bind();
};
