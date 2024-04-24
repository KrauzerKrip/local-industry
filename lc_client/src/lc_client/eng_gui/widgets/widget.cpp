#include "widget.h"

#include "lc_client/eng_gui/paint_objects/color_background.h"
#include <iostream>

Widget::Widget(Background* pBackground)
	: m_pBackground(pBackground) {
	m_position = glm::vec2(0);
	m_size = glm::vec2(0);
	m_sizePolicy = SizePolicy::RESIZE;

	m_rectangle = Rectangle();
	m_interactiveArea.m_size = glm::vec2(99999, 99999);
}

Widget::Widget(GuiDependencies dependencies) {
	m_position = glm::vec2(0);
	m_size = glm::vec2(0);
	m_sizePolicy = SizePolicy::RESIZE;
	m_pBackground = new ColorBackground(glm::vec4(0, 0, 0, 0), dependencies);

	m_rectangle = Rectangle();
	m_interactiveArea.m_size = glm::vec2(99999, 99999);
}

Widget::Widget() {
	m_position = glm::vec2(0);
	m_size = glm::vec2(0);
	m_sizePolicy = SizePolicy::RESIZE;
	m_pBackground = nullptr;

	m_rectangle = Rectangle();
	m_interactiveArea.m_size = glm::vec2(99999, 99999);
}


void Widget::show() { m_isVisible = true; }

void Widget::showWithChildren() { 
	show();

	if (m_layout.get() != nullptr) {
		m_layout->show();
	}
}

void Widget::hide() { m_isVisible = false; }

void Widget::hideWithChildren() {
	hide();

	if (m_layout.get() != nullptr) {
		m_layout->hide();
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

Layout* Widget::getLayout() { return m_layout.get(); }

void Widget::setLayout(Layout* pLayout) { m_layout = std::unique_ptr<Layout>(pLayout); }

void Widget::setBackground(Background* background) { m_pBackground = background; }

Background* Widget::getBackground() { return m_pBackground; }

std::string Widget::getName() { return m_name; }

void Widget::setName(std::string name) { m_name = name; }

SizePolicy Widget::getSizePolicy() { return m_sizePolicy; }

void Widget::setSizePolicy(SizePolicy policy) { m_sizePolicy = policy; }

void Widget::render() {
	//std::cout << m_name << " " << m_rectangle.m_absolutePosition.x << " " << m_rectangle.m_absolutePosition.y << " "
	//		  << m_rectangle.m_size.x << " " << m_rectangle.m_size.y << std::endl;

	if (m_isVisible && m_pBackground) {
		m_pBackground->render(m_rectangle, m_layer);
	}
	
	if (m_layout) {
		for (Widget* pWidget : m_layout->getChildrenWidgets()) {
			pWidget->render();
		}
	}
}

Rectangle& Widget::getRectangle() {
	return m_rectangle;
}

Layer& Widget::getLayer() { return m_layer; }

void Widget::setInteractiveArea(Rectangle rectangle) { m_interactiveArea = rectangle; }
