#include "color_background.h"


ColorBackground::ColorBackground(glm::vec4 color, const GuiDependencies& guiDependencies)
	: m_guiDependencies(guiDependencies) {
	m_color = color;
	m_hasStencil = false;
}

ColorBackground::ColorBackground(unsigned int r, unsigned int g, unsigned int b, unsigned int a,
    const GuiDependencies& guiDependencies) : m_guiDependencies((guiDependencies)) {
	m_color = glm::vec4(
		static_cast<float>(r) / 255.0f,
		static_cast<float>(g) / 255.0f,
		static_cast<float>(b) / 255.0f,
		static_cast<float>(a) / 255.0f
	);
}

void ColorBackground::setStencil(Rectangle& rectangle) { 
	m_hasStencil = true;
	m_stencil = rectangle;
}

void ColorBackground::render(const Rectangle& rectangle, const Layer& layer) {
	if (m_color.a != 0.0f) {
		if (m_hasStencil) {
			m_guiDependencies.pBackgroundRender->renderColorStencil(ColorQuad(m_color, rectangle.getVertices(),
				m_guiDependencies.pWidgetZOffsetCalculator->calculateZOffset(layer.number), 0), m_stencil.getVertices());
		}
		else {
			m_guiDependencies.pBackgroundRender->renderColor(ColorQuad(m_color, rectangle.getVertices(),
				m_guiDependencies.pWidgetZOffsetCalculator->calculateZOffset(layer.number), 0));
		}
	}
}
