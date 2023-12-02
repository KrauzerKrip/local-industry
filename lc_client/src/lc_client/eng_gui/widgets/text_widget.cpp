#include "text_widget.h"

TextWidget::TextWidget(Background background, TextWidgetDependecies dependencies)
	: Widget(background, WidgetDependecies(dependencies)) {
	m_pTextRender = dependencies.pTextRender;
}

void TextWidget::setText(std::string text) { m_text = text; }

std::string TextWidget::getText() { return m_text; }

void TextWidget::setColor(glm::vec4 color) { m_color = color; }

void TextWidget::setTextSize(unsigned int size) { m_size = size; }

void TextWidget::render() { 
	ColorQuad quad(m_background);
	quad.vertices = m_rectangle.getVertices();
	quad.zOffset = m_layer.getOffsetZ();
	
	m_pBackgroundRender->renderColor(quad);
	m_pTextRender->render(m_text, m_color, m_rectangle.m_absolutePosition, m_size, m_layer.getOffsetZ());
}
