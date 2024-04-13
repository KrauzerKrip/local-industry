#include "gl_framebuffer_controller.h"

FramebufferController::FramebufferController(IWindow* pWindow) {
	m_pWindow = pWindow; 

	pWindow->setResizeCallback([this](int width, int height) {
		if (width != 0 && height != 0) {
			this->reload();
		}
	});
}

Framebuffer* FramebufferController::getFramebuffer() { return m_pFramebuffer; }

Framebuffer* FramebufferController::getBlurFramebuffer() { return m_pBlurFramebuffer; }

void FramebufferController::reload() {
	if (m_pFramebuffer != nullptr) {
		delete m_pFramebuffer;
		m_pFramebuffer = nullptr;
	}
	if (m_pBlurFramebuffer != nullptr) {
		delete m_pBlurFramebuffer;
		m_pBlurFramebuffer = nullptr;
	}

	m_pFramebuffer = new Framebuffer(m_pWindow->getSize()[0], m_pWindow->getSize()[1], TextureType::FRAMEBUFFER);
	m_pBlurFramebuffer =
		new Framebuffer(m_pWindow->getSize()[0], m_pWindow->getSize()[1], TextureType::BLUR_FRAMEBUFFER);
}
