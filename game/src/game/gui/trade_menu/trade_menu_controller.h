#pragma once

#include <entt/entt.hpp>

#include "trade_menu_view.h"
#include "game/economy/components.h"


class TradeMenuController {
public:
	TradeMenuController(TradeMenuView* pView, entt::registry* pRegistry);

	void input();

private:
	void setOffersData(entt::entity traderEntity, PlayerAccount& account, std::vector<OfferData>& purchaseData, std::vector<OfferData>& salesData, entt::entity buyer);

	TradeMenuView* m_pView = nullptr;
	entt::registry* m_pRegistry = nullptr;
	entt::entity m_lastTrader = entt::null;
	bool m_isViewOpenFirstTime;
};