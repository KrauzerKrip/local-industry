#include "gl_framebuffer_controller.h"

FramebufferController::FramebufferController(IWindow* pWindow) {

	m_pFramebuffer = new Framebuffer(pWindow->getSize()[0], pWindow->getSize()[1], TextureType::FRAMEBUFFER);
	m_pBlurFramebuffer = new Framebuffer(pWindow->getSize()[0], pWindow->getSize()[1], TextureType::BLUR_FRAMEBUFFER);

	pWindow->setResizeCallback([this](int width, int height) {
		if (width != 0 && height != 0) {
			delete m_pFramebuffer;
			delete m_pBlurFramebuffer;
			m_pFramebuffer = new Framebuffer(width, height, TextureType::FRAMEBUFFER);
			m_pBlurFramebuffer = new Framebuffer(width, height, TextureType::BLUR_FRAMEBUFFER);
		}
	});
}

Framebuffer* FramebufferController::getFramebuffer() { return m_pFramebuffer; }

Framebuffer* FramebufferController::getBlurFramebuffer() { return m_pBlurFramebuffer; }
