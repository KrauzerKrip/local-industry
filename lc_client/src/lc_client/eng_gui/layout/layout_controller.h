#pragma once

#include <memory>
#include <vector>
#include "lc_client/eng_gui/widgets/widget.h"
#include "layouts/layout.h"
#include "widget_data.h"
#include "layout_data.h"


class LayoutController {
public:
	void update();
	std::vector<Widget*>& getWidgets();
	void show();
	void hide();
	void setLayout(std::shared_ptr<Layout> layout);

private:
	void updateLayout(LayoutData layoutData, std::vector<Widget*>& widgets);

	std::shared_ptr<Layout> m_layout;
	std::vector<Widget*> m_widgets;
};