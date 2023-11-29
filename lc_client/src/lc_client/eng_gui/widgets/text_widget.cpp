#include "text_widget.h"

TextWidget::TextWidget(Background background, BackgroundRender* pBackgroundRender, TextRender* pTextRender)
	: Widget(background, pBackgroundRender) {
	m_pBackgroundRender = pBackgroundRender;
	m_pTextRender = pTextRender;
}

void TextWidget::setText(std::string text) { m_text = text; }

std::string TextWidget::getText() { return m_text; }

void TextWidget::setColor(glm::vec4 color) { m_color = color; }

void TextWidget::setTextSize(unsigned int size) { m_size = size; }

void TextWidget::render(glm::vec2 absolutePosition, glm::vec2 size, unsigned int layer) { 
	ColorQuad quad(this->getBackground());
	quad.absolutePosition = absolutePosition;
	quad.size = size;
	quad.layer = layer;

	m_pBackgroundRender->renderColor(quad);
	m_pTextRender->render(m_text, m_color, absolutePosition, m_size, layer);
}
