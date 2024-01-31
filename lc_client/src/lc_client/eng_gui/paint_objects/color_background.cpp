#include "color_background.h"


ColorBackground::ColorBackground(glm::vec4 color, const GuiDependencies& guiDependencies)
	: m_guiDependencies(guiDependencies) {
	m_color = color;
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

void ColorBackground::render(const Rectangle& rectangle, const Layer& layer) {
	if (m_color.a != 0.0f) {
		m_guiDependencies.pBackgroundRender->renderColor(
			ColorQuad(m_color, rectangle.getVertices(), 
				m_guiDependencies.pWidgetZOffsetCalculator->calculateZOffset(layer.number)));
	}
}
