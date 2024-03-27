#include "grid.h"

Grid::Grid(unsigned int columnNumber, float padding, float rowHeight)
	: m_columnNumber(columnNumber),
	  m_padding(padding),
	  m_rowHeight(rowHeight) {}

void Grid::updateChildWidgets() {
	float cursorX = m_padding;
	float cursorY = m_size.y - m_rowHeight - m_padding;

	unsigned int columnNumber = 0;
	for (Widget* widget : m_widgets) {
		columnNumber++;

		widget->getRectangle().m_size = widget->getSize();

		glm::vec2 position = glm::vec2(0);
		position.y = cursorY;
		position.x = cursorX;

		widget->getRectangle().m_absolutePosition = position;

		cursorX += widget->getRectangle().m_size.x + m_padding;

		if (columnNumber == m_columnNumber) {
			columnNumber = 0;
			cursorY -= (m_padding + m_rowHeight);
		}
	}
}
