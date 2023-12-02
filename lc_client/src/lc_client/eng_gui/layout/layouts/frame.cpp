#include "frame.h"

#include <iterator>

void Frame::updateChildWidgets() {
	for (std::shared_ptr<Widget> widget : m_widgets) {
		widget->getRectangle().m_absolutePosition += widget->getPosition();
		widget->getRectangle().m_size = widget->getSize();
	}
}
