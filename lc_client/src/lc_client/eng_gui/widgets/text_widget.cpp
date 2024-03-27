#include "text_widget.h"

TextWidget::TextWidget(Background* background, GuiDependencies dependencies)
	: Widget(background),
	  m_textDependencies(dependencies) {
	m_pTextRender = dependencies.pTextRender;
	m_textColor = glm::vec4(0, 0, 0, 1);
	m_textSize = 16;
}

TextWidget::TextWidget(GuiDependencies dependencies)
	: Widget(GuiDependencies(dependencies)),
	  m_textDependencies(dependencies) {
	m_pTextRender = dependencies.pTextRender;
	m_textColor = glm::vec4(0, 0, 0, 1);
	m_textSize = 16;
}

void TextWidget::setText(std::string text) { m_text = text; }

std::string TextWidget::getText() { return m_text; }

void TextWidget::setTextColor(glm::vec4 color) { m_textColor = color; }

void TextWidget::setTextColor(unsigned r, unsigned g, unsigned b, unsigned a) {
	m_textColor = glm::vec4(
		static_cast<float>(r) / 255.0f,
		static_cast<float>(g) / 255.0f,
		static_cast<float>(b) / 255.0f,
		static_cast<float>(a) / 255.0f
	);
}

void TextWidget::setTextSize(unsigned int size) { m_textSize = size; }

void TextWidget::render() { 
	if (m_isVisible) {
		//ColorQuad quad(m_background);
		//quad.vertices = m_rectangle.getVertices();
		//quad.zOffset = m_textDependencies.pWidgetZOffsetCalculator->calculateZOffset(m_layer.number);

		m_textLayer.number = (m_layer.number);

		m_background->render(m_rectangle, m_layer);

		glm::vec2 textPos =  m_rectangle.m_absolutePosition;
		textPos += (m_rectangle.m_size / 2.0f);

		m_pTextRender->renderCentered(m_text, m_textColor, textPos, m_textSize,
			m_textDependencies.pTextZOffsetCalculator->calculateZOffset(m_textLayer.number));
	}
}
