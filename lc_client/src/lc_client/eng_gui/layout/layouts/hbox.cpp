#include "hbox.h"

HBox::HBox() {
    m_padding = glm::vec2(0);
	m_mode = BoxMode::STRETCH_WIDGETS;
}

void HBox::setPadding(unsigned x, unsigned y) { m_padding = glm::vec2(x, y); }

void HBox::setPadding(glm::vec2 padding) { m_padding = padding; }

void HBox::updateChildWidgets() {
	float cursorX = m_padding.y;

	if (m_mode == BoxMode::STRETCH_WIDGETS) {
		for (std::shared_ptr<Widget>& widget : m_widgets) {
			float sizeX = m_size.x / static_cast<float>(m_widgets.size()) - 1.5 * m_padding.x;
			widget->getRectangle().m_size.x = sizeX;
			widget->getRectangle().m_size.y = m_size.y - m_padding.y * 2;

			glm::vec2 position = glm::vec2(0);

			position.x = cursorX;
			position.y += m_padding.x;

			cursorX += widget->getRectangle().m_size.x + m_padding.x;

			widget->getRectangle().m_absolutePosition += position;
		}
	}
	else if (m_mode == BoxMode::STRETCH_PADDING) {
		float usableSpace = m_size.x - 2 * m_padding.x;
		float widgetSizeXSum = 0;
		for (std::shared_ptr<Widget>& widget : m_widgets) {
			widgetSizeXSum += widget->getRectangle().m_size.x;
		}

		float freeSpace = usableSpace - widgetSizeXSum;
		unsigned int innerPaddingX = 0;
		if (m_widgets.size() > 1) {
			innerPaddingX = static_cast<unsigned int>(freeSpace / m_widgets.size() - 1);
		}

		for (std::shared_ptr<Widget>& widget : m_widgets) {
			widget->getRectangle().m_size.x = widget->getSize().x;
			widget->getRectangle().m_size.y = m_size.y - m_padding.y * 2.0f;

			glm::vec2 position = glm::vec2(0);

			cursorX -= widget->getRectangle().m_size.x + m_padding.x * 2.0f;

			position.x = cursorX;
			position.y += m_padding.y;

			widget->getRectangle().m_absolutePosition += position;
		}
	}

}

void HBox::setBoxMode(BoxMode mode) {
    m_mode = mode;
}
