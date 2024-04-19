#include "trade_system.h"

#include <stdexcept>

#include "components.h"
#include "game/inventory/components.h"


TradeSystem::TradeSystem(entt::registry* pRegistry) { m_pRegistry = pRegistry; }

void TradeSystem::update() { 
	entt::entity accountEntity = entt::null;
	auto accounts = m_pRegistry->view<PlayerAccount>();
	for (entt::entity entity : accounts) {
		accountEntity = entity;
	}
	if (!m_pRegistry->valid(accountEntity)) {
		throw std::runtime_error("No valid entity containing PlayerAccount (economy) component detected!");
	}
	PlayerAccount& account = m_pRegistry->get<PlayerAccount>(accountEntity);

	auto tradesInProgress = m_pRegistry->view<TradeInProgress>();
	for (auto&& [entity, trade] : tradesInProgress.each()) {
		if (m_pRegistry->all_of<InventoryPlaced>(entity)) {
			account.funds -= trade.priceSum;
		}
		else {
			
		}
		m_pRegistry->remove<TradeInProgress>(entity);
	}

	auto tradeRequests = m_pRegistry->view<TradeRequest, Inventory>();
	for (auto&& [entity, request, inventory] : tradeRequests.each()) {
		Trader& trader = m_pRegistry->get<Trader>(request.trader);
		if (trader.offers.find(request.goods) != trader.offers.end()) {
			unsigned int priceSum = trader.offers.at(request.goods) * request.quantity;
			if (account.funds >= priceSum) {
				m_pRegistry->emplace<InventoryPlacement>(entity, InventoryPlacement(entity, request.goods, request.quantity));
				m_pRegistry->emplace<TradeInProgress>(entity, TradeInProgress(priceSum));
			}
		}

		m_pRegistry->remove<TradeRequest>(entity);
	}
}
