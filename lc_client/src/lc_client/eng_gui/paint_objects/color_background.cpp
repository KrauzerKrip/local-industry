#include "color_background.h"


ColorBackground::ColorBackground(glm::vec4 color, const GuiDependencies& guiDependencies)
	: m_guiDependencies(guiDependencies) {
	m_color = color;
}

void ColorBackground::render(const Rectangle& rectangle, const Layer& layer) {
	if (m_color.a != 0.0f) {
		m_guiDependencies.pBackgroundRender->renderColor(
			ColorQuad(m_color, rectangle.getVertices(), 
				m_guiDependencies.pWidgetZOffsetCalculator->calculateZOffset(layer.number)));
	}
}