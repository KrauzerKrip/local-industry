#include "text_widget.h"

TextWidget::TextWidget(Background background, TextWidgetDependecies dependencies)
	: Widget(background, WidgetDependecies(dependencies)), m_textDependencies(dependencies), m_textLayer(dependencies.pTextZOffsetCalculator) {
	m_pTextRender = dependencies.pTextRender;
	m_color = glm::vec4(0, 0, 0, 1);
}

TextWidget::TextWidget(TextWidgetDependecies dependencies)
	: Widget(WidgetDependecies(dependencies)),
	  m_textDependencies(dependencies),
	  m_textLayer(dependencies.pTextZOffsetCalculator) {
	m_pTextRender = dependencies.pTextRender;
	m_color = glm::vec4(0, 0, 0, 1);
}

void TextWidget::setText(std::string text) { m_text = text; }

std::string TextWidget::getText() { return m_text; }

void TextWidget::setColor(glm::vec4 color) { m_color = color; }

void TextWidget::setTextSize(unsigned int size) { m_textSize = size; }

void TextWidget::render() { 
	if (m_isVisible) {
		ColorQuad quad(m_background);
		quad.vertices = m_rectangle.getVertices();
		quad.zOffset = m_layer.getOffsetZ();

		m_textLayer.setLayerNumber(m_layer.getLayerNumber());

		if (m_background.getColor().a != 0) {
			m_pBackgroundRender->renderColor(quad);
		}

		glm::vec2 textPos =  m_rectangle.m_absolutePosition;
		textPos += (m_size / 2.0f);

		m_pTextRender->renderCentered(
			m_text, m_color, textPos, m_textSize, m_textLayer.getOffsetZ());
	}
}
