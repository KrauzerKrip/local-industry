#pragma once

#include "lc_client/eng_graphics/texture.h"


/**
 * The general rule is
that if you never need to sample data from a specific buffer, it is wise to use a renderbuffer object for
that specific buffer. If you need to sample data from a specific buffer like colors or depth values, you
should use a texture attachment instead.
 */
class Framebuffer {
public:
	Framebuffer(int width, int height, TextureType type);
	~Framebuffer();

    void bind();
	void bindTexture();

protected:
	unsigned int m_fbo;
	unsigned int m_rbo;
	unsigned int m_texture;
	TextureType m_textureType;
};

