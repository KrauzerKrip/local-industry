#include "trade_menu_controller.h"

#include <iostream>

#include "game/economy/components.h"
#include "game/control/components.h"
#include "game/item/components.h"
#include "game/character/components.h"
#include "game/inventory/components.h"


TradeMenuController::TradeMenuController(TradeMenuView* pView, entt::registry* pRegistry) {
	m_pView = pView;
	m_pRegistry = pRegistry;
}

void TradeMenuController::input() { 
	entt::entity accountEntity = entt::null;
	auto accounts = m_pRegistry->view<PlayerAccount>();
	for (entt::entity entity : accounts) {
		accountEntity = entity;
	}
	if (!m_pRegistry->valid(accountEntity)) {
		throw std::runtime_error("No valid entity containing PlayerAccount (economy) component detected!");
	}
	PlayerAccount& account = m_pRegistry->get<PlayerAccount>(accountEntity);

	auto selectedTraders = m_pRegistry->view<Trader, Selected>();
	
	entt::entity traderEntity = entt::null;

	std::vector<OfferData> purchaseData;
	std::vector<OfferData> salesData;
	for (auto&& [entity, trader] : selectedTraders.each()) {
		traderEntity = entity;
		for (auto [item, price] : trader.purchaseOffers) {
			OfferData data;
			data.iconPath = "gmod_vibe";
			data.label = m_pRegistry->get<Item>(item).name;
			data.priceLabel = std::to_string(price);
			data.buttonLabel = "Buy";
			data.callback = [this, entity, item]() { 
				auto view = m_pRegistry->view<GameCharacter>();
				for (auto character : view) {
					m_pRegistry->emplace<PurchaseRequest>(character, PurchaseRequest(entity, item, 1));
				}
				};
			if (price <= account.funds) {
				data.affordable = true;
			}
			else {
				data.affordable = false;
			}
			purchaseData.push_back(data);
		}
		for (auto [item, price] : trader.saleOffers) {
			OfferData data;
			data.iconPath = "gmod_vibe";
			data.label = m_pRegistry->get<Item>(item).name;
			data.priceLabel = std::to_string(price);
			data.buttonLabel = "Sell";
			data.callback = [this, entity, item]() {
				auto view = m_pRegistry->view<GameCharacter>();
				for (auto character : view) {
					m_pRegistry->emplace<SaleRequest>(character, SaleRequest(entity, item, 1));
				}
			};
			data.affordable = false;
			auto view = m_pRegistry->view<GameCharacter, Inventory>();
			for (auto [ent, character, inventory] : view.each()) {
				if (inventory.items.find(item) != inventory.items.end()) {
					if (1 <= inventory.items.at(item)) {
						data.affordable = true;
					}
				}
			}

			salesData.push_back(data);
		}
	}

	if (m_pRegistry->valid(traderEntity)) {
		m_pView->setPurchasesData(purchaseData);
		m_pView->setSalesData(salesData);
		m_pView->showWithChildren();
		m_pRegistry->remove<Selected>(traderEntity);
	}

}
