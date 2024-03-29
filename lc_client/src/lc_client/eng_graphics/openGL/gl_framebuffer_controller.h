#pragma once

#include "gl_window.h"
#include "gl_framebuffer.h"


class FramebufferController {
public:
	FramebufferController(IWindow* pWindow);
	
	Framebuffer* getFramebuffer();
	Framebuffer* getBlurFramebuffer();

private:
	Framebuffer* m_pFramebuffer = nullptr;
	Framebuffer* m_pBlurFramebuffer = nullptr;
};