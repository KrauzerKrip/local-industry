module;

#include <entt/entt.hpp>

#include "game/control/components.h"
#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_scene/entt/components.h"
#include <lc_client/eng_model/entt/components.h>
#include <lc_client/eng_npc/components.h>
#include <lc_client/eng_physics/entt/components.h>

export module character:character_system;
import :components;
import :character_task_system;


export class CharacterSystem {
public:
	CharacterSystem(entt::registry* pRegistry) { 
		m_pRegistry = pRegistry; 
		m_pCharacterTaskSystem = new CharacterTaskSystem(pRegistry);

	}
	~CharacterSystem() {}

	void input() {
		const auto selectedGameCharacters = m_pRegistry->view<GameCharacter, Selected>(entt::exclude<Outline>);
		for (auto&& [entity, character] : selectedGameCharacters.each()) {
			m_pRegistry->emplace<Outline>(entity, glm::vec3(0, 1, 1), 0.1f);
		}

		const auto unselectedGameCharacters = m_pRegistry->view<GameCharacter, Outline>(entt::exclude<Selected>);
		for (auto&& [entity, character, outline] : unselectedGameCharacters.each()) {
			m_pRegistry->remove<Outline>(entity);
		}
	}

	void update() {
		if (!m_isEveryCharacterCreated) {
			// For some reason creating characters in constructor causes invalid entity script error.
			createCharacters();
			m_isEveryCharacterCreated = true;
		}

		m_pCharacterTaskSystem->update();
	}

private:
	void createCharacters() {
	    entt::entity entity = m_pRegistry->create();
		m_pRegistry->emplace<Properties>(entity, Properties("character_emmy", ""));
		m_pRegistry->emplace<Transform>(entity, Transform(glm::vec3(0, 0,2), glm::vec3(0,0,0), glm::vec3(1, 1, 1)));
		m_pRegistry->emplace<ModelRequest>(entity, ModelRequest("dev", "test_cube_white"));
		m_pRegistry->emplace<GameCharacter>(entity, GameCharacter("emmy"));
		m_pRegistry->emplace<Npc>(entity, Npc(2));
		m_pRegistry->emplace<Selectable>(entity, Selectable());
		m_pRegistry->emplace<BoxCollider>(entity, BoxCollider(2, 2, 2));
		m_pRegistry->emplace<TaskQueue>(entity, TaskQueue());
	}

	entt::registry* m_pRegistry = nullptr;
	
	CharacterTaskSystem* m_pCharacterTaskSystem = nullptr;

    bool m_isEveryCharacterCreated = false;
};