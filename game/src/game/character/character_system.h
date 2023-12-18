#pragma once

#include <entt/entt.hpp>


class CharacterSystem {
public:
	CharacterSystem(entt::registry* pRegistry);
	~CharacterSystem();

	void input();
	void update();

private:
	entt::registry* m_pRegistry;
};
