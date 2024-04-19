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
	std::unordered_map<entt::entity, unsigned int> offers;
};

struct TradeRequest {
	entt::entity trader;
	entt::entity goods;
	unsigned int quantity;

	TradeRequest(entt::entity trader, entt::entity goods, unsigned int quantity)
		: trader(trader),
		  goods(goods),
		  quantity(quantity) {}
};

struct TradeInProgress {
	unsigned int priceSum;
	
	TradeInProgress(unsigned int priceSum) : priceSum(priceSum) {}
};

struct BlueprintTrader {

};