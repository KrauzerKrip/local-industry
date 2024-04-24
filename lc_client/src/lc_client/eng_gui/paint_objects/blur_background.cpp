#include "blur_background.h"

BlurBackground::BlurBackground(glm::vec4 color, float blurIntensity, const GuiDependencies& guiDependencies)
	: m_guiDependencies(guiDependencies) {
	m_color = color;
	m_blurIntensity = blurIntensity;  
	m_hasStencil = false;
}

BlurBackground::BlurBackground(unsigned int r, unsigned int g, unsigned int b, unsigned a,
	float blurIntensity, const GuiDependencies& guiDependencies)
	: m_guiDependencies((guiDependencies)) {
	m_color = glm::vec4(static_cast<float>(r) / 255.0f, static_cast<float>(g) / 255.0f, static_cast<float>(b) / 255.0f,
			static_cast<float>(a) / 255.0f);
	m_blurIntensity = blurIntensity;
}

void BlurBackground::setStencil(Rectangle& rectangle) { 
	m_hasStencil = true;
	m_stencil = rectangle;
}

void BlurBackground::render(const Rectangle& rectangle, const Layer& layer) {
	if (m_color.a != 0.0f) {
		if (m_hasStencil) {
			m_guiDependencies.pBackgroundRender->renderColorStencil(ColorQuad(m_color, rectangle.getVertices(),
				m_guiDependencies.pWidgetZOffsetCalculator->calculateZOffset(layer.number), m_blurIntensity), m_stencil.getVertices());
		}
		else {
			m_guiDependencies.pBackgroundRender->renderColor(ColorQuad(m_color, rectangle.getVertices(),
				m_guiDependencies.pWidgetZOffsetCalculator->calculateZOffset(layer.number), m_blurIntensity));
		}
	}
}
