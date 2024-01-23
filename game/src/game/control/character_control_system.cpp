#include "character_control_system.h"

#include <iostream>

#include <glm/ext/matrix_projection.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "lc_client/eng_physics/entt/components.h"
#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_scene/entt/components.h"
#include "components.h"
#include "lc_client/eng_npc/components.h"

import character;



CharacterControlSystem::CharacterControlSystem(entt::registry* pRegistry) { m_pRegistry = pRegistry; }

void CharacterControlSystem::input() { 

}

void CharacterControlSystem::update() {}

void CharacterControlSystem::onAction(std::string action, entt::entity entity, glm::vec3 position, float distance) {
	if (action == "kb_select") {
		if (m_pRegistry->all_of<Selectable>(entity)) {
			return;
		}

		if (m_pRegistry->all_of<Walkable>(entity)) {
			auto selectedCharacters = m_pRegistry->view<GameCharacter, Selected>();

			for (auto&& [entity, character] : selectedCharacters.each()) {
				m_pRegistry->emplace_or_replace<Waypoint>(entity, Waypoint(position));
			}
		}
	}
}

void CharacterControlSystem::onMouseMove(entt::entity entity, glm::vec3 position, float distance) {}
