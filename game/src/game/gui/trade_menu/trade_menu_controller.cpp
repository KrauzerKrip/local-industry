#include "trade_menu_controller.h"

#include "game/economy/components.h"
#include "game/control/components.h"
#include "game/item/components.h"


TradeMenuController::TradeMenuController(TradeMenuView* pView, entt::registry* pRegistry) {
	m_pView = pView;
	m_pRegistry = pRegistry;
}

void TradeMenuController::input() { 
	auto selectedTraders = m_pRegistry->view<Trader, Selected>();
	std::vector<OfferData> offersData;
	for (auto&& [entity, trader] : selectedTraders.each()) {
		for (auto [item, price] : trader.offers) {
			OfferData data;
			data.iconPath = "gmod_vibe";
			data.label = m_pRegistry->get<Item>(item).name;
			data.priceLabel = std::to_string(price);
			data.buttonLabel = "Buy";
			offersData.push_back(data);
		}
	}
	m_pView->setData(offersData);
}
