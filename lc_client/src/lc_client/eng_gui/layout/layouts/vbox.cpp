#include "vbox.h"

void VBox::updateChildWidgets() { 
	float cursorY = m_size.y;

	if (m_widgets.size() > 0) {
		cursorY -= m_widgets.at(0)->getRectangle().m_size.y;
	}

	for (std::shared_ptr<Widget>& widget : m_widgets) {
		widget->getRectangle().m_size = widget->getSize();

		glm::vec2 position = glm::vec2(0);

		position.y = cursorY;

		cursorY -= widget->getRectangle().m_size.y;

		widget->getRectangle().m_absolutePosition = position;
	}
}
