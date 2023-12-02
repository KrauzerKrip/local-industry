#include "vbox.h"

void VBox::updateChildWidgets() { 
	float cursorY = 0.0f;

	for (std::shared_ptr<Widget>& widget : m_widgets) {
		widget->getRectangle().m_size = widget->getSize();

		glm::vec2 position;
		position.x = m_position.x;

		position.y = cursorY;

		cursorY = widget->getRectangle().m_size.y;

		widget->getRectangle().m_absolutePosition = position;
	}
}
