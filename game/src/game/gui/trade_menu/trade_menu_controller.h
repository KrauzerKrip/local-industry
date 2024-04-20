#pragma once

#include <entt/entt.hpp>

#include "trade_menu_view.h"


class TradeMenuController {
public:
	TradeMenuController(TradeMenuView* pView, entt::registry* pRegistry);

	void input();

private:
	TradeMenuView* m_pView = nullptr;
	entt::registry* m_pRegistry = nullptr;
};