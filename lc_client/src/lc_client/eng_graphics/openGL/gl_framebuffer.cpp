#include "gl_framebuffer.h"

#include <glad/glad.h>


Framebuffer::Framebuffer() {
	glGenFramebuffers(1, &m_id);

	//if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {

	//}
}

Framebuffer::~Framebuffer() { glDeleteFramebuffers(1, &m_id); }

void Framebuffer::bind() { glBindFramebuffer(GL_FRAMEBUFFER, m_id); }

FramebufferTexture::FramebufferTexture(int width, int height) {
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindFramebuffer(GL_FRAMEBUFFER, m_id);
	
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);
}

FramebufferTexture::~FramebufferTexture() {}

void FramebufferTexture::bind() { 
	glBindFramebuffer(GL_FRAMEBUFFER, m_id);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

FramebufferRenderbuffer::FramebufferRenderbuffer(int width, int height) {
	glGenRenderbuffers(1, &m_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

	glBindFramebuffer(GL_FRAMEBUFFER, m_id);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
}

FramebufferRenderbuffer::~FramebufferRenderbuffer() {}

void FramebufferRenderbuffer::bind() { glBindRenderbuffer(GL_RENDERBUFFER, m_rbo); }
