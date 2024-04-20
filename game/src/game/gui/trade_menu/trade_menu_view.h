#pragma once

#include <vector>

#include "lc_client/eng_gui/includes.h"
#include "trade_menu_slot.h"


struct OfferData {
	std::string iconPath;
	std::string label;
	std::string buttonLabel;
	std::string priceLabel;
	std::function<void()> callback;
};


class TradeMenuView : public Widget {
public:
	TradeMenuView(GuiDependencies dependencies);

	void render() override;
	void setData(std::vector<OfferData> offersData);

private:
	std::vector<TradeMenuSlot*> m_slots;

	TextWidget* m_pLabel = nullptr;
};