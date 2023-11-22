#pragma once

#include <vector>
#include <utility>
#include "layout.h"
#include "lc_client/eng_gui/widgets/widget.h"
#include "lc_client/eng_gui/widgets/text_widget.h"


class Frame : public Layout {
public:
	Frame();

	std::vector<std::shared_ptr<Widget>> getChildrenWidgets();
	void updateChildWidget(WidgetData& widgetData);
	void renderChildren();
	void addChild(std::shared_ptr<Widget> widget);

private:
	std::vector<std::shared_ptr<Widget>> m_widgets;
};
