#include "vertical_scroll_area.h"

#include <iostream>


VerticalScrollArea::VerticalScrollArea() { 
	m_scroll = 0.0f;
	m_spacing = 0;
	m_contentSize = 0;
	m_notFittingSize = 0;
}

void VerticalScrollArea::updateChildWidgets() {
	bool isFirst = true;
	float cursorY = m_size.y;

	for (Widget* pWidget : m_widgets) {
		float sizeY = pWidget->getSize().y;
		pWidget->getRectangle().m_size.y = sizeY;
		pWidget->getRectangle().m_size.x = m_size.x;

		glm::vec2 position = glm::vec2(0);

		if (isFirst) {
			cursorY -= pWidget->getRectangle().m_size.y;
		}
		else { 
			cursorY -= pWidget->getRectangle().m_size.y + m_spacing;
		}
		isFirst = false;

		position.y = cursorY;

		pWidget->getRectangle().m_absolutePosition += position;
	}

	int usedSpace = -(cursorY - m_size.y);
	int notFittingSize = -(m_size.y - usedSpace);
	int spaceToScroll = static_cast<int>(notFittingSize * m_scroll);
	for (Widget* pWidget : m_widgets) {
		pWidget->getRectangle().m_absolutePosition.y += spaceToScroll;
	}

	std::cout << m_scroll << std::endl;

	m_contentSize = usedSpace;
	m_notFittingSize = notFittingSize;
}

float VerticalScrollArea::getScroll() { return m_scroll; }

void VerticalScrollArea::setScroll(float scroll) { m_scroll = scroll; }

void VerticalScrollArea::setSpacing(unsigned int spacing) { m_spacing = spacing; }

void VerticalScrollArea::scroll(float offset) { 
	m_scroll -= 1 * offset / m_notFittingSize;

	if (m_scroll < 0) {
		m_scroll = 0;
	}
	if (m_scroll > 1) {
		m_scroll = 1;
	}
}

int VerticalScrollArea::getContentSize() { return m_contentSize; }

int VerticalScrollArea::getNotFittingSize() { return m_notFittingSize; }