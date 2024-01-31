#include "percentage_pane.h"

void PercentagePane::addWidget(Widget* pWidget, glm::vec2 percentagePosition, glm::vec2 percentageSize) {
	m_percentageWidgets.emplace_back(pWidget, percentagePosition, percentageSize);
	this->addChild(pWidget);
}

void PercentagePane::updateChildWidgets() {
    for (auto& percentageWidget : m_percentageWidgets) {
		Widget* pWidget = percentageWidget.pWidget;
		glm::vec2 percPos = percentageWidget.percentagePosition;
		glm::vec2 percSize = percentageWidget.percentageSize;

		pWidget->getRectangle().m_absolutePosition.x += percPos.x * m_size.x;
		pWidget->getRectangle().m_absolutePosition.y += percPos.y * m_size.y;
		pWidget->getRectangle().m_size.x = static_cast<int>(percSize.x * m_size.x);
		pWidget->getRectangle().m_size.y = static_cast<int>(percSize.y * m_size.y);
    }
}
