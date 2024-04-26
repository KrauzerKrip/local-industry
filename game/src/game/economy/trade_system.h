#pragma once

#include <entt/entt.hpp>

#include "components.h"


class TradeSystem {
public:
	TradeSystem(entt::registry* pRegistry);

	void update();

private:
	void processPurchases(PlayerAccount& account);
	void processSales(PlayerAccount& account);

	entt::registry* m_pRegistry = nullptr;
};