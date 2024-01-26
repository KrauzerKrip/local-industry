#include "text_widget.h"

TextWidget::TextWidget(Background* background, GuiDependencies dependencies)
	: Widget(background),
	  m_textDependencies(dependencies) {
	m_pTextRender = dependencies.pTextRender;
	m_color = glm::vec4(0, 0, 0, 1);
}

TextWidget::TextWidget(GuiDependencies dependencies)
	: Widget(GuiDependencies(dependencies)),
	  m_textDependencies(dependencies) {
	m_pTextRender = dependencies.pTextRender;
	m_color = glm::vec4(0, 0, 0, 1);
}

void TextWidget::setText(std::string text) { m_text = text; }

std::string TextWidget::getText() { return m_text; }

void TextWidget::setColor(glm::vec4 color) { m_color = color; }

void TextWidget::setTextSize(unsigned int size) { m_textSize = size; }

void TextWidget::render() { 
	if (m_isVisible) {
		//ColorQuad quad(m_background);
		//quad.vertices = m_rectangle.getVertices();
		//quad.zOffset = m_textDependencies.pWidgetZOffsetCalculator->calculateZOffset(m_layer.number);

		m_textLayer.number = (m_layer.number);

		m_background->render(m_rectangle, m_layer);

		glm::vec2 textPos =  m_rectangle.m_absolutePosition;
		textPos += (m_size / 2.0f);

		m_pTextRender->renderCentered(m_text, m_color, textPos, m_textSize,
			m_textDependencies.pTextZOffsetCalculator->calculateZOffset(m_textLayer.number));
	}
}
