#include "frame.h"

#include <iterator>

Frame::Frame() {}

std::vector<std::shared_ptr<Widget>> Frame::getChildrenWidgets() { 
	return m_widgets; }

void Frame::updateChildWidget(Widget& widget) {
	widget.getRectangle().m_absolutePosition += widget.getPosition();
	widget.getRectangle().m_size = widget.getSize();
}
 
void Frame::renderChildren() {
	//for (std::shared_ptr<Widget> widget : m_widgets) {
	//	widget->render();
	//}
}

void Frame::addChild(std::shared_ptr<Widget> widget) { m_widgets.push_back(widget); }
