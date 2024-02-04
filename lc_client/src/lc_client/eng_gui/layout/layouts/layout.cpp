#include "layout.h"


Layout::~Layout() {
    for (Widget* pWidget : m_widgets) {
        delete pWidget;
    }
}

std::vector<Widget*>& Layout::getChildrenWidgets() { return m_widgets; }

void Layout::addChild(Widget* pWidget) { m_widgets.push_back(pWidget); }

void Layout::show() {
    for (Widget* pWidget : m_widgets) {
		pWidget->showWithChildren();
    }
}

void Layout::hide() {
	for (Widget* pWidget : m_widgets) {
		pWidget->hideWithChildren();
	}
}
