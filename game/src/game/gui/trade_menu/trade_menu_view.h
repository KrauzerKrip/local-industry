#pragma once

#include <vector>

#include "lc_client/eng_gui/includes.h"
#include "game/gui/window_widget.h"
#include "trade_menu_slot.h"


struct OfferData {
	std::string iconPath;
	std::string label;
	std::string buttonLabel;
	std::string priceLabel;
	std::function<void()> callback;
};

enum class ActiveTab {
	PURCHASES,
	SALES
};

class TradeMenuView : public WindowWidget {
public:
	TradeMenuView(GuiDependencies dependencies);

	void render() override;
	void setPurchasesData(std::vector<OfferData> offersData);
	void setSalesData(std::vector<OfferData> offersData);
	void show() override;

private:
	std::vector<TradeMenuSlot*> m_purchaseSlots;
	std::vector<TradeMenuSlot*> m_saleSlots;

	std::vector<Widget*> m_purchaseScrollWidgets;
	std::vector<Widget*> m_saleScrollWidgets;

	float m_purchasesScroll;
	float m_salesScroll;

	ActiveTab m_activeTab;

	ScrollWidget* m_pScrollWidget = nullptr;
};