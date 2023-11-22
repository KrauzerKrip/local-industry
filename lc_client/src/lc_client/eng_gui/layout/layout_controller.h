#pragma once

#include <memory>
#include <vector>
#include "lc_client/eng_gui/controller/i_text_controller.h"
#include "lc_client/eng_gui/widgets/widget.h"
#include "layouts/layout.h"
#include "widget_data.h"
#include "layout_data.h"


class LayoutController {
public:
	void update();
	std::vector<WidgetData>& getWidgets();
	void show();
	void hide();
	void setLayout(std::shared_ptr<Layout> layout);

private:
	void updateLayout(LayoutData layoutData, std::vector<WidgetData>& widgets);

	std::shared_ptr<Layout> m_layout;
	std::unique_ptr<ITextController> m_textController;
	std::vector<WidgetData> m_widgets;
};