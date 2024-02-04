#include "frame.h"

#include <iterator>

void Frame::updateChildWidgets() {
	for (Widget* widget : m_widgets) {
		widget->getRectangle().m_absolutePosition += widget->getPosition();
		widget->getRectangle().m_size = widget->getSize();
	}
}
