#include "widget.h"

Widget::Widget(Background background, WidgetDependecies dependencies)
	: m_background(background),
	  m_layer(dependencies.pZOffsetCalculator) {
	m_pBackgroundRender = dependencies.pBackgroundRender;
	m_position = glm::vec2(0);
	m_size = glm::vec2(0);

	m_rectangle = Rectangle();
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

void Widget::render() { 
	m_pBackgroundRender->renderColor(ColorQuad(m_background, m_rectangle.getVertices(), m_layer.getOffsetZ()));
}

Rectangle& Widget::getRectangle() {
	return m_rectangle;
}

Layer& Widget::getLayer() { return m_layer; }
