#pragma once

#include "lc_client/eng_graphics/texture.h"
#include "lc_client/util/image.h"


class TextureGL : public Texture{
public:
	TextureGL(std::shared_ptr<eng::Image> image);

	void load();
	void unload();
	void bind();
	void setTextureType(TextureType textureType);
	int getId();

private:
	unsigned int m_textureGl;
};
