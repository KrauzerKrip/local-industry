#include "anchor_pane.h"

void Anchor::addWidget(Widget* pWidget) {
	this->addWidget(
		pWidget, WidgetSides::TOP | WidgetSides::BOTTOM | WidgetSides::LEFT | WidgetSides::RIGHT);
}

void Anchor::addWidget(Widget* pWidget, const WidgetSides sides) {
	m_widgets.push_back(AnchoredWidget({pWidget, sides}));
}

void Anchor::updateChildWidgets(glm::vec2 paneSize) {
	glm::vec2 position(m_percentagePosition.x * paneSize.x, m_percentagePosition.y * paneSize.y);

    if (m_pGizmoWidget) {
		m_pGizmoWidget->getRectangle().m_absolutePosition += position;
		m_pGizmoWidget->getLayer().number = 100;
    }

    for (AnchoredWidget anchoredWidget : m_widgets) {
		Widget* pWidget = anchoredWidget.pWidget;
		WidgetSides sides = anchoredWidget.widgetSides;
		//glm::vec2 percentageSize = anchoredWidget.percentageSize;

        if (checkSide(sides, WidgetSides::TOP) && checkSide(sides, WidgetSides::BOTTOM) &&
			checkSide(sides, WidgetSides::LEFT) && checkSide(sides, WidgetSides::RIGHT)) {
			pWidget->getRectangle().m_absolutePosition += position;
			//pWidget->getRectangle().m_size = glm::vec2(percentageSize.x * paneSize.x, percentageSize.y * paneSize.y);
        }
    }
}

bool Anchor::checkSide(WidgetSides sides, WidgetSides side) {
	return ((sides & side) != WidgetSides::NONE);
}


void AnchorPane::addAnchor(Anchor* pAnchor) {
    m_anchors.push_back(pAnchor);

    for (AnchoredWidget anchoredWidget : pAnchor->m_widgets) {
		this->addChild(anchoredWidget.pWidget);
    }

    if (pAnchor->m_pGizmoWidget) {
		this->addChild(pAnchor->m_pGizmoWidget);
    }
}

void AnchorPane::updateChildWidgets() {
    for (Anchor* pAnchor : m_anchors) {
		pAnchor->updateChildWidgets(m_size);    
    }
}
