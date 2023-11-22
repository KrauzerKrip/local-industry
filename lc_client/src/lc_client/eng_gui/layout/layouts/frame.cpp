#include "frame.h"

#include <iterator>

Frame::Frame() {}

std::vector<std::shared_ptr<Widget>> Frame::getChildrenWidgets() { 
	return m_widgets; }

void Frame::updateChildWidget(WidgetData& widgetData) {
	widgetData.position += widgetData.widget->getPosition();
	widgetData.size = widgetData.widget->getSize();
}
 
void Frame::renderChildren() {
	for (std::shared_ptr<Widget> widget : m_widgets) {
		widget->render();
	}
}

void Frame::addChild(std::shared_ptr<Widget> widget) { m_widgets.push_back(widget); }
