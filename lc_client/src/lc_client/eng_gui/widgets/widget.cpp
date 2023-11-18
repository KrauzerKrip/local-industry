#include "widget.h"

void Widget::show() { m_isVisible = true; }

void Widget::hide() { m_isVisible = false; }

glm::vec2 Widget::getSize() { return m_size; }

void Widget::setSize(glm::vec2 size) { m_size = size; }

glm::vec2 Widget::getPosition() { return m_position; }

void Widget::setPosition(glm::vec2 position) { m_position = position; }

std::shared_ptr<Layout> Widget::getLayout() { return m_layout; }

void Widget::setBackground(Background background) {}

void Widget::render() {}

std::array<glm::vec2, 4> Widget::getVertices() { return m_vertices; }

void Widget::setVertices(std::array<glm::vec2, 4> vertices) { m_vertices = vertices; }
