#include "character_system.h"
#include "task_queue.h"

void CharacterSystem::input() {
	const auto selectedGameCharacters = m_pRegistry->view<GameCharacter, Selected>(entt::exclude<Outline>);
	for (auto&& [entity, character] : selectedGameCharacters.each()) {
		m_pRegistry->emplace<Outline>(entity, glm::vec3(0, 1, 1), 0.1f);
	}

	const auto unselectedGameCharacters = m_pRegistry->view<GameCharacter, Outline>(entt::exclude<Selected>);
	for (auto&& [entity, character, outline] : unselectedGameCharacters.each()) {
		m_pRegistry->remove<Outline>(entity);
	}
}

void CharacterSystem::update(double updateInterval) {
	if (!m_isEveryCharacterCreated) {
		// For some reason creating characters in constructor causes invalid entity script error.
		createCharacters();
		m_isEveryCharacterCreated = true;
	}

	m_pCharacterTaskSystem->update(updateInterval);
}

void CharacterSystem::createCharacters() {
	entt::entity entity = m_pRegistry->create();
	m_pRegistry->emplace<Properties>(entity, Properties("character_emmy", ""));
	m_pRegistry->emplace<Transform>(entity, Transform(glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));
	m_pRegistry->emplace<ModelRequest>(entity, ModelRequest("dev", "test_cube_white"));
	m_pRegistry->emplace<GameCharacter>(entity, GameCharacter("emmy"));
	m_pRegistry->emplace<Npc>(entity, Npc(10));
	m_pRegistry->emplace<Selectable>(entity, Selectable());
	m_pRegistry->emplace<TaskQueue>(entity, TaskQueue());
	m_pRegistry->emplace<Inventory>(entity, Inventory(9, 5));
}