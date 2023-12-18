#include "character_system.h"

#include "components.h"
#include "game/control/components.h"
#include "lc_client/eng_graphics/entt/components.h"


CharacterSystem::CharacterSystem(entt::registry* pRegistry) { m_pRegistry = pRegistry; }

CharacterSystem::~CharacterSystem() {}

void CharacterSystem::input() { 
	auto selectedGameCharacters = m_pRegistry->view<GameCharacter, Selected>(entt::exclude<Outline>);
	for (auto&& [entity, character] : selectedGameCharacters.each()) {
		m_pRegistry->emplace<Outline>(entity, glm::vec3(0, 1, 1), 0.1f);
	}

	auto unselectedGameCharacters = m_pRegistry->view<GameCharacter, Outline>(entt::exclude<Selected>);
	for (auto&& [entity, character, outline] : unselectedGameCharacters.each()) {
		m_pRegistry->remove<Outline>(entity);
	}
}

void CharacterSystem::update() {  }
