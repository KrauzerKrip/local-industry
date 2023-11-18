#include "frame.h"

#include <iterator>

Frame::Frame() {}

std::vector<Widget> Frame::getChildrenWidgets() { 
	return m_widgets; }

void Frame::updateChildWidget(Widget& widget) {
	auto vertices = widget.getVertices();

	for (glm::vec2& vertice : vertices) {
		vertice += widget.getPosition();
	}

	widget.setVertices(vertices);
}
