#pragma once

#include <memory>
#include <vector>
#include "lc_client/eng_gui/widgets/widget.h"
#include "layouts/layout.h"
#include "widget_data.h"
#include "layout_data.h"


class LayoutController {
public:
	~LayoutController();
	void update();
	std::vector<Widget*>& getWidgets();
	void show();
	void hide();
	void setLayout(Layout* pLayout);

private:
	void updateLayout(LayoutData layoutData, std::vector<Widget*>& widgets);

	std::unique_ptr<Layout> m_layout;
	std::vector<Widget*> m_widgets;
};