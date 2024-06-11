#pragma once

#include <entt/entt.hpp>

#include "game/control/components.h"
#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_scene/entt/components.h"
#include <lc_client/eng_model/entt/components.h>
#include <lc_client/eng_npc/components.h>
#include <lc_client/eng_physics/entt/components.h>
#include "game/inventory/components.h"

#include "components.h"

#include "character_task_system.h"

class CharacterSystem {
public:
	CharacterSystem(entt::registry* pRegistry) {
		m_pRegistry = pRegistry;
		m_pCharacterTaskSystem = new CharacterTaskSystem(pRegistry);
	}
	~CharacterSystem() {}

	void input();
	void update(double updateInterval);

private:
	void createCharacters();

	entt::registry* m_pRegistry = nullptr;

	CharacterTaskSystem* m_pCharacterTaskSystem = nullptr;

	bool m_isEveryCharacterCreated = false;
};