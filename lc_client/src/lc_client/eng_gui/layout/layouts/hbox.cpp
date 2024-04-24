#include "hbox.h"

#include <iostream>


HBox::HBox() {
    m_padding = glm::vec2(0);
	m_mode = BoxMode::STRETCH_WIDGETS;
	m_spacing = 0;
}

void HBox::setPadding(unsigned x, unsigned y) { m_padding = glm::vec2(x, y); }

void HBox::setPadding(glm::vec2 padding) { m_padding = padding; }

void HBox::updateChildWidgets() {
	float cursorX = m_padding.x;
	bool isFirst = true;

	if (m_mode == BoxMode::STRETCH_WIDGETS) {
		int resizableWidgetsCount = 0;
		float fixedWidgetSizeXSum = 0;

		for (Widget* pWidget : m_widgets) {
			if (pWidget->getSizePolicy() == SizePolicy::FIXED) {
				fixedWidgetSizeXSum += pWidget->getRectangle().m_size.x;
			}
			else {
				resizableWidgetsCount++;
			}
		}

		float freeSpace = m_size.x - fixedWidgetSizeXSum;

		for (Widget* pWidget : m_widgets) {
			float sizeX = pWidget->getSize().x;
			if (pWidget->getSizePolicy() == SizePolicy::RESIZE) {
				sizeX = (freeSpace / static_cast<float>(resizableWidgetsCount) - m_spacing - m_padding.x * 0.5f);
			}
			pWidget->getRectangle().m_size.x = sizeX;
			pWidget->getRectangle().m_size.y = m_size.y - m_padding.y * 2;

			glm::vec2 position = glm::vec2(0);

			position.x = cursorX;
			position.y += m_padding.y;

			cursorX += pWidget->getRectangle().m_size.x + m_spacing;

			pWidget->getRectangle().m_absolutePosition += position;
		}
	}
	else if (m_mode == BoxMode::STRETCH_SPACING) {
		float usableSpace = m_size.x - 2 * m_padding.x;
		float widgetSizeXSum = 0;
		for (Widget* widget : m_widgets) {
			widgetSizeXSum += widget->getRectangle().m_size.x;
		}

		float freeSpace = usableSpace - widgetSizeXSum;
		unsigned int spacing = 0;
		if (m_widgets.size() > 1) {
			spacing = static_cast<unsigned int>(freeSpace / (m_widgets.size() - 1));
		}

		for (Widget* widget : m_widgets) {
			widget->getRectangle().m_size.x = widget->getSize().x;
			widget->getRectangle().m_size.y = m_size.y - m_padding.y * 2.0f;

			glm::vec2 position = glm::vec2(0);

			position.x = cursorX;
			position.y += m_padding.y;

			cursorX += widget->getRectangle().m_size.x + spacing;

			//cursorX += widget->getRectangle().m_size.x + m_padding.x * 2.0f;

			widget->getRectangle().m_absolutePosition += position;
		}
	}

}

void HBox::setSpacing(unsigned int spacing) { m_spacing = spacing; }

void HBox::setBoxMode(BoxMode mode) {
    m_mode = mode;
}
