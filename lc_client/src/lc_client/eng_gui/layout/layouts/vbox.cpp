#include "vbox.h"

VBox::VBox() {
    m_padding = glm::vec2(0);
	m_mode = BoxMode::STRETCH_WIDGETS;
}

void VBox::setPadding(unsigned x, unsigned y) { m_padding = glm::vec2(x, y); }

void VBox::setPadding(glm::vec2 padding) { m_padding = padding; }


void VBox::updateChildWidgets() { 
	float cursorY = m_size.y;

	if (m_mode == BoxMode::STRETCH_WIDGETS) {
		for (std::shared_ptr<Widget>& widget : m_widgets) {
			float sizeY = m_size.y / static_cast<float>(m_widgets.size()) - 1.5 * m_padding.y;
			widget->getRectangle().m_size.y = sizeY;
			widget->getRectangle().m_size.x = m_size.x - m_padding.x * 2;

			glm::vec2 position = glm::vec2(0);

		    cursorY -= widget->getRectangle().m_size.y + m_padding.y;

			position.y = cursorY;
			position.x += m_padding.x;

			widget->getRectangle().m_absolutePosition += position;
		}
	}
	else if (m_mode == BoxMode::STRETCH_PADDING) {
	    float usableSpace = m_size.y - 2 * m_padding.y;
		float widgetSizeYSum = 0; 
	    for (std::shared_ptr<Widget>& widget : m_widgets) {
			widgetSizeYSum += widget->getRectangle().m_size.y;
		}

		float freeSpace = usableSpace - widgetSizeYSum;
		unsigned int innerPaddingY = 0;
		if (m_widgets.size() > 1) {
            innerPaddingY = static_cast<unsigned int>(freeSpace / m_widgets.size() - 1);
		}

	    for (std::shared_ptr<Widget>& widget : m_widgets) {
			widget->getRectangle().m_size.y = widget->getSize().y;
			widget->getRectangle().m_size.x = m_size.x - m_padding.x * 2.0f;

			glm::vec2 position = glm::vec2(0);

			cursorY -= widget->getRectangle().m_size.y + m_padding.y*2.0f;

			position.y = cursorY;
			position.x += m_padding.x;

			widget->getRectangle().m_absolutePosition += position;
		}

	}
}

void VBox::setMode(BoxMode mode) { m_mode = mode; }
