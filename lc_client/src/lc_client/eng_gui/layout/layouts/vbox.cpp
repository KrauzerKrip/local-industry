#include "vbox.h"

VBox::VBox() {
    m_padding = glm::vec2(0);
	m_mode = BoxMode::STRETCH_WIDGETS;
	m_spacing = 0;
}

void VBox::setPadding(unsigned x, unsigned y) { m_padding = glm::vec2(x, y); }

void VBox::setPadding(glm::vec2 padding) { m_padding = padding; }

void VBox::setSpacing(unsigned spacing) { m_spacing = spacing; }

void VBox::updateChildWidgets() { 
	float cursorY = m_size.y - m_padding.y;
	bool isFirst = true;

	if (m_mode == BoxMode::STRETCH_WIDGETS) {
		for (std::shared_ptr<Widget>& widget : m_widgets) {
			float sizeY = (m_size.y - 2 * m_padding.y + m_spacing) / static_cast<float>(m_widgets.size()) - m_spacing;
			widget->getRectangle().m_size.y = sizeY;
			widget->getRectangle().m_size.x = m_size.x - m_padding.x * 2;

			glm::vec2 position = glm::vec2(0);

			if (isFirst) {
				cursorY -= widget->getRectangle().m_size.y;   
			}
			else {
				cursorY -= widget->getRectangle().m_size.y + m_spacing;  
			}
			isFirst = false;

			position.y = cursorY;
			position.x += m_padding.x;

			widget->getRectangle().m_absolutePosition += position;
		}
	}
	else if (m_mode == BoxMode::STRETCH_SPACING) {
	    float usableSpace = m_size.y - 2 * m_padding.y;
		float widgetSizeYSum = 0; 
	    for (std::shared_ptr<Widget>& widget : m_widgets) {
			widgetSizeYSum += widget->getRectangle().m_size.y;
		}

		float freeSpace = usableSpace - widgetSizeYSum;
		unsigned int spacing = 0;
		if (m_widgets.size() > 1) {
            spacing = static_cast<unsigned int>(freeSpace / (m_widgets.size() - 1));
		}

	    for (std::shared_ptr<Widget>& widget : m_widgets) {
			widget->getRectangle().m_size.y = widget->getSize().y;
			widget->getRectangle().m_size.x = m_size.x - m_padding.x * 2.0f;

			glm::vec2 position = glm::vec2(0);

			if (isFirst) {
				cursorY -= widget->getRectangle().m_size.y;
			}
			else {
				cursorY -= widget->getRectangle().m_size.y + spacing;
			}
			isFirst = false;

			position.y = cursorY;
			position.x += m_padding.x;

			widget->getRectangle().m_absolutePosition += position;
		}

	}
}

void VBox::setMode(BoxMode mode) { m_mode = mode; }
