#include "trade_system.h"

#include <stdexcept>

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

	this->processPurchases(account);
	this->processSales(account);
}

void TradeSystem::processPurchases(PlayerAccount& account) {
	auto purchasesInProgress = m_pRegistry->view<PurchaseInProgress>();
	for (auto&& [entity, trade] : purchasesInProgress.each()) {
		if (m_pRegistry->all_of<InventoryPlaced>(entity)) {
			account.funds -= trade.priceSum;
			m_pRegistry->remove<InventoryPlaced>(entity);
		}
		else {
			m_pRegistry->remove<InventoryCantPlace>(entity);
		}
		m_pRegistry->remove<PurchaseInProgress>(entity);
	}

	auto purchaseRequests = m_pRegistry->view<PurchaseRequest, Inventory>(entt::exclude<PurchaseInProgress, InventoryPlacement>);
	for (auto&& [entity, request, inventory] : purchaseRequests.each()) {
		Trader& trader = m_pRegistry->get<Trader>(request.trader);
		if (trader.purchaseOffers.find(request.goods) != trader.purchaseOffers.end()) {
			unsigned int priceSum = trader.purchaseOffers.at(request.goods) * request.quantity;
			if (account.funds >= priceSum) {
				m_pRegistry->emplace<InventoryPlacement>(
					entity, InventoryPlacement(entity, request.goods, request.quantity));
				m_pRegistry->emplace<PurchaseInProgress>(entity, PurchaseInProgress(priceSum));
			}
		}

		m_pRegistry->remove<PurchaseRequest>(entity);
	}
}

void TradeSystem::processSales(PlayerAccount& account) {
	auto salesInProgress = m_pRegistry->view<SaleInProgress>();
	for (auto&& [entity, trade] : salesInProgress.each()) {
		if (m_pRegistry->all_of<InventoryWithdrawn>(entity)) {
			account.funds += trade.priceSum;
			m_pRegistry->remove<InventoryWithdrawn>(entity);
		}
		else {
			m_pRegistry->remove<InventoryCantWithdraw>(entity);
		}
		m_pRegistry->remove<SaleInProgress>(entity);
	}

	auto saleRequests = m_pRegistry->view<SaleRequest, Inventory>(entt::exclude<SaleInProgress, InventoryWithdrawal>);
	for (auto&& [entity, request, inventory] : saleRequests.each()) {
		Trader& trader = m_pRegistry->get<Trader>(request.trader);

		if (trader.saleOffers.find(request.goods) != trader.saleOffers.end()) {
			unsigned int priceSum = trader.saleOffers.at(request.goods) * request.quantity;
			m_pRegistry->emplace<InventoryWithdrawal>(entity, InventoryWithdrawal(entity, request.goods, request.quantity));
			m_pRegistry->emplace<SaleInProgress>(entity, SaleInProgress(priceSum));
		}

		m_pRegistry->remove<SaleRequest>(entity);
	}
}
