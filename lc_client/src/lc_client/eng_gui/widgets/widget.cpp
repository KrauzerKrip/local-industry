#include "widget.h"

Widget::Widget(Background background, RenderBackground* pBackgroundRender) : m_background(background)
{
	m_pBackroundRender = pBackgroundRender;
	m_position = glm::vec2(0);
	m_size = glm::vec2(0);
}

void Widget::show() { m_isVisible = true; }

void Widget::hide() { m_isVisible = false; }

glm::vec2 Widget::getSize() { return m_size; }

void Widget::setSize(glm::vec2 size) { m_size = size; }

glm::vec2 Widget::getPosition() { return m_position; }

void Widget::setPosition(glm::vec2 position) { m_position = position; }

std::shared_ptr<Layout> Widget::getLayout() { return m_layout; }

void Widget::setLayout(std::shared_ptr<Layout> layout) { m_layout = layout; }

void Widget::setBackground(Background background) {}

Background Widget::getBackground() { return m_background; }

void Widget::render(glm::vec2 absolutePosition, glm::vec2 size, unsigned int layer) { 
	m_pBackroundRender->renderColor(ColorQuad(m_background, absolutePosition, size, layer));
}
