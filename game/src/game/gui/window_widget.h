#pragma once

#include "lc_client/eng_gui/widgets/widget.h"
#include "lc_client/eng_gui/widgets/text_widget.h"


class WindowWidget : public Widget {
public:
	WindowWidget(GuiDependencies dependencies);
	void setLabel(std::string label);
	void setContentLayout(Layout* pLayout);
	void render() override;

private:
	Widget* m_pContentSpaceWidget = nullptr;
	TextWidget* m_pLabel = nullptr;
};

