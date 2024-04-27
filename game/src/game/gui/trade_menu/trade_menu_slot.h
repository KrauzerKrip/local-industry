#pragma once


#include "lc_client/eng_gui/includes.h"


class TradeMenuSlot : public Widget {
public:
	TradeMenuSlot(GuiDependencies dependencies);

	void setIcon(std::string path);
	void setLabel(std::string label);
	void setButtonLabel(std::string buttonLabel);
	void setPriceLabel(std::string price);
	void setCallback(std::function<void()> callback);
	void setAffordable(bool value);
	void showWithChildren() override;

private:
	Widget* m_pIcon = nullptr;
	TextWidget* m_pLabel = nullptr;
	TextWidget* m_pQuantity = nullptr;
	TextWidget* m_pPrice = nullptr;
	Button* m_pButton = nullptr;

	Background* m_pAffordableBackground = nullptr;
	Background* m_pUnaffordableBackground = nullptr;
	Background* m_pButtonBackground = nullptr;
	Background* m_pHoverButtonBackground = nullptr;
	Background* m_pOffButtonBackground = nullptr;

	std::function<void()> m_callback;

	bool m_isAffordable;

	GuiDependencies m_dependencies;
};