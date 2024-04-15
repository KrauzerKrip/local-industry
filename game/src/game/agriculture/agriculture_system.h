#pragma once

#include <entt/entt.hpp>


class AgricultureSystem {
public:
	AgricultureSystem(entt::registry* pRegistry);

	void update();

private:
	entt::registry* m_pRegistry = nullptr;
};