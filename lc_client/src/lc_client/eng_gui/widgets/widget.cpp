#include "widget.h"

Widget::Widget(Background background, RenderBackground* pBackgroundRender) : m_background(background)
{
	m_pBackroundRender = pBackgroundRender; 
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

void Widget::render() {
	//m_pBackroundRender->addToQueue(m_background, m_vertices);
	//m_layout->renderChildren();
}
