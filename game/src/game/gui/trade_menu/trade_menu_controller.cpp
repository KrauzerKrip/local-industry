#include "trade_menu_controller.h"

#include <iostream>

#include "game/economy/components.h"
#include "game/control/components.h"
#include "game/item/components.h"
#include "game/character/components.h"


TradeMenuController::TradeMenuController(TradeMenuView* pView, entt::registry* pRegistry) {
	m_pView = pView;
	m_pRegistry = pRegistry;
}

void TradeMenuController::input() { 
	auto selectedTraders = m_pRegistry->view<Trader, Selected>();
	
	entt::entity traderEntity = entt::null;

	std::vector<OfferData> offersData;
	for (auto&& [entity, trader] : selectedTraders.each()) {
		traderEntity = entity;
		for (auto [item, price] : trader.purchaseOffers) {
			OfferData data;
			data.iconPath = "gmod_vibe";
			data.label = m_pRegistry->get<Item>(item).name;
			data.priceLabel = std::to_string(price);
			data.buttonLabel = "Buy";
			data.callback = [this, entity, item]() { 
				m_pView->hideWithChildren();
				auto view = m_pRegistry->view<GameCharacter>();
				for (auto character : view) {
					m_pRegistry->emplace<PurchaseRequest>(character, PurchaseRequest(entity, item, 1));
				}
				};
			offersData.push_back(data);
		}
	}

	if (m_pRegistry->valid(traderEntity)) {
		m_pView->setData(offersData);
		m_pView->showWithChildren();
		m_pRegistry->remove<Selected>(traderEntity);
	}

}
