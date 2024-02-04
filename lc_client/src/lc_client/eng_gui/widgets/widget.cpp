#include "widget.h"

#include "lc_client/eng_gui/paint_objects/color_background.h"
#include <iostream>

Widget::Widget(Background* pBackground)
	: m_background(pBackground) {
	m_position = glm::vec2(0);
	m_size = glm::vec2(0);

	m_rectangle = Rectangle();
}

Widget::Widget(GuiDependencies dependencies) {
	m_position = glm::vec2(0);
	m_size = glm::vec2(0);
	m_background = std::make_unique<ColorBackground>(glm::vec4(0, 0, 0, 0), dependencies);

	m_rectangle = Rectangle();
}

Widget::Widget() {
	m_position = glm::vec2(0);
	m_size = glm::vec2(0);
	m_background = nullptr;

	m_rectangle = Rectangle();
}


void Widget::show() { m_isVisible = true; }

void Widget::showWithChildren() { 
	show();

	if (m_layout.get() != nullptr) {
		std::vector<Widget*> widgets =  m_layout->getChildrenWidgets();

		for (Widget* pWidget : widgets) {
			pWidget->showWithChildren();
		}
	}
}

void Widget::hide() { m_isVisible = false; }

void Widget::hideWithChildren() {
	hide();

	if (m_layout.get() != nullptr) {
		std::vector<Widget*> widgets = m_layout->getChildrenWidgets();

		for (Widget* pWidget : widgets) {
			pWidget->hideWithChildren();
		}
	}
}

void Widget::toggle() {
	if (this->isVisible()) {
		this->hide();
	}
	else {
		this->show();
	}
}

void Widget::toggleWithChildren() {
	if (this->isVisible()) {
		this->hideWithChildren();
	}
	else {
		this->showWithChildren();
	}
}

bool Widget::isVisible() { return m_isVisible; }

glm::vec2 Widget::getSize() { return m_size; }

void Widget::setSize(glm::vec2 size) { m_size = size; }

void Widget::setSize(unsigned width, unsigned height) { m_size = glm::vec2(width, height); }

glm::vec2 Widget::getPosition() { return m_position; }

void Widget::setPosition(glm::vec2 position) { m_position = position; }

void Widget::setPosition(unsigned x, unsigned y) { m_position = glm::vec2(x, y);  }

std::shared_ptr<Layout> Widget::getLayout() { return m_layout; }

void Widget::setLayout(std::shared_ptr<Layout> layout) { m_layout = layout; }
void Widget::setLayout(Layout* pLayout) { m_layout = std::shared_ptr<Layout>(pLayout); }

void Widget::setBackground(Background* background) { m_background = std::unique_ptr<Background>(background); }

Background* Widget::getBackground() { return m_background.get(); }

void Widget::setName(std::string name) { m_name = name; }

void Widget::render() {
	std::cout << m_name << " " << m_rectangle.m_absolutePosition.x << " " << m_rectangle.m_absolutePosition.y << " "
			  << m_rectangle.m_size.x << " " << m_rectangle.m_size.y << std::endl;

	if (m_isVisible && m_background) {
		m_background->render(m_rectangle, m_layer);
	}
}

Rectangle& Widget::getRectangle() {
	return m_rectangle;
}

Layer& Widget::getLayer() { return m_layer; }
