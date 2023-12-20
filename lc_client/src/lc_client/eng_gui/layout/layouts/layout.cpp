#include "layout.h"



std::vector<std::shared_ptr<Widget>> Layout::getChildrenWidgets() { return m_widgets; }

void Layout::addChild(std::shared_ptr<Widget> widget) { m_widgets.push_back(widget); }
void Layout::addChild(Widget* pWidget) { m_widgets.push_back(std::shared_ptr<Widget>(pWidget)); }
