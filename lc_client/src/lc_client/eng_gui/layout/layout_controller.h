#pragma once

#include <memory>
#include <vector>
#include "lc_client/eng_gui/widgets/widget.h"
#include "layouts/layout.h"
#include "widget_data.h"
#include "layout_data.h"
#include "lc_client/eng_gui/pointer_over_gui_impl.h"


class LayoutController {
public:
	LayoutController(PointerOverGuiImpl* pPointerOverGui, InputController* pInputController);
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

	PointerOverGuiImpl* m_pPointerOverGui = nullptr;
	InputController* m_pInputController = nullptr;
};