#pragma once

#include <vector>
#include <utility>
#include "layout.h"
#include "lc_client/eng_gui/widgets/widget.h"
#include "lc_client/eng_gui/widgets/text_widget.h"

class Frame : Layout {
public:
	Frame();

	std::vector<Widget> getChildrenWidgets();
	void updateChildWidget(Widget& widgetData);

private:
	std::vector<Widget> m_widgets;
};
