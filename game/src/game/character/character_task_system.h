#pragma once

#include <iostream>

#include <entt/entt.hpp>

#include "game/machine/components.h"
#include "lc_client/eng_npc/components.h"
#include <lc_client/eng_model/entt/components.h>
#include <lc_client/eng_physics/entt/components.h>
#include "components.h"
#include "game/control/components.h"

class CharacterTaskSystem {
public:
	CharacterTaskSystem(entt::registry* pRegistry) { m_pRegistry = pRegistry; }

	void update(double updateInterval);
	void processTaskRequests();
	void processRemoveTaskRequests();

	// it may bug if there are more than one request (some request may be lost).
	void assignTasksToCharacters();

	void removeCharacterTasks(entt::entity charEnt);
	void queueTasks();
	void processTasks(double updateInterval);
	float getTaskAreaRadius(const Colliders& colliders) const;


private:
	entt::registry* m_pRegistry = nullptr;
};