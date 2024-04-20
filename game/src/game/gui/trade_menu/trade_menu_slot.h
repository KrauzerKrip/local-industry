#pragma once


#include "lc_client/eng_gui/includes.h"


class TradeMenuSlot : public Widget {
public:
	TradeMenuSlot(GuiDependencies dependencies);

	void setIcon(std::string path);
	void setLabel(std::string label);
	void setButtonLabel(std::string buttonLabel);
	void setPriceLabel(std::string price);

private:
	Widget* m_pIcon = nullptr;
	TextWidget* m_pLabel = nullptr;
	TextWidget* m_pQuantity = nullptr;
	TextWidget* m_pPrice = nullptr;
	Button* m_pButton = nullptr;

	GuiDependencies m_dependencies;
};