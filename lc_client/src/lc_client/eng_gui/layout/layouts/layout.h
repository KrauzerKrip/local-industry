#pragma once

#include <vector>
#include <memory>
#include "lc_client/eng_gui/widgets/widget.h"
#include "lc_client/eng_gui/layout/widget_data.h"

class Widget;

class Layout {
public:
	virtual ~Layout(){};

	virtual std::vector<std::shared_ptr<Widget>> getChildrenWidgets() = 0;
	virtual void updateChildWidget(WidgetData& widgetData) = 0;
	virtual void renderChildren() = 0;
	virtual void addChild(std::shared_ptr<Widget> widget) = 0;
};
