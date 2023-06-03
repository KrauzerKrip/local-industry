#pragma once

#include "lc_client/eng_graphics/texture.h"
#include "lc_client/util/image.h"

struct CubemapMaterial {
	eng::Image right;
	eng::Image left;
	eng::Image top;
	eng::Image bottom;
	eng::Image back;
	eng::Image front;
};

class TextureCubemapGl : public Texture {
public:
	TextureCubemapGl(std::shared_ptr<CubemapMaterial> material);

	void load();
	void unload();
	void bind();
	void setTextureType(TextureType textureType){};
	int getId(){};

private:
	unsigned int m_texture;
	std::shared_ptr<CubemapMaterial> m_material;
};
