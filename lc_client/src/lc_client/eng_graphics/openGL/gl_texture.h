#pragma once

#include "lc_client/eng_graphics/texture.h"
#include "lc_client/util/image.h"


class TextureGL : public Texture{
public:
	TextureGL(eng::Image* pImage);

	void load();
	void unload();
	void bind();
	void setTextureType(TextureType textureType);
	int getId();

private:
	unsigned int m_textureGl;
	std::unique_ptr<eng::Image> m_image;
};
