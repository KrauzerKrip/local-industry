#pragma once



/**
 * The general rule is
that if you never need to sample data from a specific buffer, it is wise to use a renderbuffer object for
that specific buffer. If you need to sample data from a specific buffer like colors or depth values, you
should use a texture attachment instead.
 */
class Framebuffer {
public:
	Framebuffer();
	~Framebuffer();

	virtual void bind();

protected:
	unsigned int m_id;
};

class FramebufferTexture : public Framebuffer {
public:
	FramebufferTexture(int width, int height);
	~FramebufferTexture();

	void bind();

private:
	unsigned int m_texture;
};

class FramebufferRenderbuffer : public Framebuffer {
public:
	FramebufferRenderbuffer(int width, int height);
	~FramebufferRenderbuffer();

	void bind();

private:
	unsigned int m_rbo;
};
