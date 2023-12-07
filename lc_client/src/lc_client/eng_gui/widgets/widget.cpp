#include "widget.h"

Widget::Widget(Background background, WidgetDependecies dependencies)
	: m_background(background),
	  m_layer(dependencies.pZOffsetCalculator) {
	m_pBackgroundRender = dependencies.pBackgroundRender;
	m_position = glm::vec2(0);
	m_size = glm::vec2(0);

	m_rectangle = Rectangle();
}

Widget::Widget(WidgetDependecies dependencies) : m_layer(dependencies.pZOffsetCalculator), m_background(Background(glm::vec4(0))) {
	m_pBackgroundRender = dependencies.pBackgroundRender;
	m_position = glm::vec2(0);
	m_size = glm::vec2(0);

	m_rectangle = Rectangle();
}

void Widget::show() { m_isVisible = true; }

void Widget::showWithChildren() { 
	show();

	if (m_layout.get() != nullptr) {
		std::vector<std::shared_ptr<Widget>> widgets =  m_layout->getChildrenWidgets();

		for (std::shared_ptr<Widget> widget : widgets) {
			widget->showWithChildren();
		}
	}
}

void Widget::hide() { m_isVisible = false; }

void Widget::hideWithChildren() {
	hide();

	if (m_layout.get() != nullptr) {
		std::vector<std::shared_ptr<Widget>> widgets = m_layout->getChildrenWidgets();

		for (std::shared_ptr<Widget> widget : widgets) {
			widget->hideWithChildren();
		}
	}
}

glm::vec2 Widget::getSize() { return m_size; }

void Widget::setSize(glm::vec2 size) { m_size = size; }

glm::vec2 Widget::getPosition() { return m_position; }

void Widget::setPosition(glm::vec2 position) { m_position = position; }

std::shared_ptr<Layout> Widget::getLayout() { return m_layout; }

void Widget::setLayout(std::shared_ptr<Layout> layout) { m_layout = layout; }

void Widget::setBackground(Background background) { m_background = background; }

Background Widget::getBackground() { return m_background; }

void Widget::setName(std::string name) { m_name = name; }

void Widget::render() { 
	if (m_isVisible) {
		if (m_background.getColor().a != 0) {
			m_pBackgroundRender->renderColor(ColorQuad(m_background, m_rectangle.getVertices(), m_layer.getOffsetZ()));
		}
	}
}

Rectangle& Widget::getRectangle() {
	return m_rectangle;
}

Layer& Widget::getLayer() { return m_layer; }
