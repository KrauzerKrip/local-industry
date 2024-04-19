#pragma once

#include <entt/entt.hpp>


class TradeSystem {
public:
	TradeSystem(entt::registry* pRegistry);

	void update();

private:
	entt::registry* m_pRegistry = nullptr;
};