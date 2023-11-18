#pragma once

#include <vector>
#include "lc_client/eng_gui/widgets/widget.h"

class Layout {
public:
	virtual ~Layout() = 0;

	virtual std::vector<Widget> getChildrenWidgets() = 0;
	virtual void updateChildWidget(Widget& widgetData) = 0;
};
