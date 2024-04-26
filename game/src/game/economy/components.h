#pragma once

#include <entt/entt.hpp>

#include <unordered_map>
#include <string>


struct PlayerAccount {
	unsigned int funds;

	PlayerAccount() : funds(0) {}
	PlayerAccount(unsigned int funds) : funds(funds) {}
};

struct Trader {
	std::unordered_map<entt::entity, unsigned int> purchaseOffers;
	std::unordered_map<entt::entity, unsigned int> saleOffers;
};

struct PurchaseRequest {
	entt::entity trader;
	entt::entity goods;
	unsigned int quantity;

	PurchaseRequest(entt::entity trader, entt::entity goods, unsigned int quantity)
		: trader(trader),
		  goods(goods),
		  quantity(quantity) {}
};

struct SaleRequest {
	entt::entity trader;
	entt::entity goods;
	unsigned int quantity;

	SaleRequest(entt::entity trader, entt::entity goods, unsigned int quantity)
		: trader(trader),
		  goods(goods),
		  quantity(quantity) {}
};

struct PurchaseInProgress {
	unsigned int priceSum;
	
	PurchaseInProgress(unsigned int priceSum) : priceSum(priceSum) {}
};

struct SaleInProgress {
	unsigned int priceSum;

	SaleInProgress(unsigned int priceSum) : priceSum(priceSum) {}
};

struct BlueprintTrader {

};