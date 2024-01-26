#include "widget.h"

#include "lc_client/eng_gui/paint_objects/color_background.h"

Widget::Widget(Background* pBackground)
	: m_background(pBackground) {
	m_position = glm::vec2(0);
	m_size = glm::vec2(0);
	m_background = std::unique_ptr<Background>(pBackground);

	m_rectangle = Rectangle();
}

Widget::Widget(GuiDependencies dependencies) {
	m_position = glm::vec2(0);
	m_size = glm::vec2(0);
	m_background = std::make_unique<ColorBackground>(glm::vec4(0, 0, 0, 0), dependencies);

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

bool Widget::isVisible() { return m_isVisible; }

glm::vec2 Widget::getSize() { return m_size; }

void Widget::setSize(glm::vec2 size) { m_size = size; }

glm::vec2 Widget::getPosition() { return m_position; }

void Widget::setPosition(glm::vec2 position) { m_position = position; }

std::shared_ptr<Layout> Widget::getLayout() { return m_layout; }

void Widget::setLayout(std::shared_ptr<Layout> layout) { m_layout = layout; }
void Widget::setLayout(Layout* pLayout) { m_layout = std::shared_ptr<Layout>(pLayout); }

void Widget::setBackground(Background* background) { m_background = std::unique_ptr<Background>(background); }

Background* Widget::getBackground() { return m_background.get(); }

void Widget::setName(std::string name) { m_name = name; }

void Widget::render() { 
	if (m_isVisible) {
		m_background->render(m_rectangle, m_layer);
	}
}

Rectangle& Widget::getRectangle() {
	return m_rectangle;
}

Layer& Widget::getLayer() { return m_layer; }
