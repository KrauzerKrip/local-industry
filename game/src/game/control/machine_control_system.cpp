#include "machine_control_system.h"

#include <iostream>

#include "game/control/components.h"
#include "game/machine/components.h"
#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_scene/entt/components.h"

import character;


MachineControlSystem::MachineControlSystem(
	MouseRaycast* pMouseRaycast, ActionControl* pActionControl, entt::registry* pRegistry) {
	m_pMouseRaycast = pMouseRaycast;
	m_pActionControl = pActionControl;
	m_pRegistry = pRegistry;

	addSelectionCallback();
}

void MachineControlSystem::input() {
	auto selectedBlueprints = m_pRegistry->view<Blueprint, Selected, Transform, RelativeTransform>();

	if (selectedBlueprints.begin() != selectedBlueprints.end()) {
		RaycastResult result = m_pMouseRaycast->doMouseRaycast(entt::exclude<Blueprint>);
		if (result.intersectionPoint.has_value()) {
			for (auto&& [ent, transform,  relativeTransform] : selectedBlueprints.each()) {
				transform.position = relativeTransform.transform.position + result.intersectionPoint.value();
				transform.position.x = (int)transform.position.x;
				transform.position.y = (int)transform.position.y;
				transform.position.z = (int)transform.position.z;
			}
		}
	}
}

void MachineControlSystem::update() {

}

void MachineControlSystem::onAction(std::string action, entt::entity entity, glm::vec3 position, float distance) { 
	if (action == "kb_build") {
		if (m_pRegistry->all_of<Blueprint>(entity)) {
			if (m_pRegistry->all_of<Task>(entity)) {
				m_pRegistry->remove<Task>(entity);
				if (m_pRegistry->all_of<CharacterAssignedTo>(entity)) {
					m_pRegistry->remove<CharacterAssignedTo>(entity);
				}
			}
			else {
				auto selectedCharacter = m_pRegistry->view<GameCharacter, Selected>();
				for (auto&& [characterEntity, character] : selectedCharacter.each()) {
					m_pRegistry->emplace<CharacterAssignedTo>(entity, characterEntity);
				}
				m_pRegistry->emplace<Task>(entity);
			}
		}
	}
}

void MachineControlSystem::onMouseMove(entt::entity entity, glm::vec3 position, float distance) {

}

void MachineControlSystem::addSelectionCallback() {
	m_pActionControl->addActionCallback("kb_select", [this]() {
		RaycastResult result = m_pMouseRaycast->doMouseRaycast();

		auto selectedBlueprints = m_pRegistry->view<Blueprint, Selected>();

		Outline outline(glm::vec3(255 / 255., 255 / 255., 255 / 255.), 0.025);

		if (selectedBlueprints.begin() == selectedBlueprints.end()) {
			if (result.entityIntersectedWith.has_value()) {
				entt::entity entIntersect = result.entityIntersectedWith.value();
				if (m_pRegistry->all_of<Blueprint>(entIntersect)) {
					m_pRegistry->emplace_or_replace<Selected>(entIntersect);
					m_pRegistry->emplace_or_replace<Outline>(entIntersect, outline);
				}
			}

			return;
		}

		for (auto&& [entity] : selectedBlueprints.each()) {
			if (result.entityIntersectedWith.has_value()) {
				entt::entity entIntersect = result.entityIntersectedWith.value();
				if (entity == entIntersect) {
					m_pRegistry->remove<Selected>(entity);
					m_pRegistry->remove<Outline>(entity);
				}
				else {
					m_pRegistry->remove<Selected>(entity);
					m_pRegistry->remove<Outline>(entity);
					if (m_pRegistry->all_of<Blueprint>(entIntersect)) {
						m_pRegistry->emplace_or_replace<Selected>(entIntersect);
						m_pRegistry->emplace_or_replace<Outline>(entIntersect, outline);
					}
				}
			}
			else {
				m_pRegistry->remove<Selected>(entity);
				m_pRegistry->remove<Outline>(entity);
			}
		}

		auto initBlueprints = m_pRegistry->view<Blueprint, BlueprintInit>();

		for (auto&& [entity] : initBlueprints.each()) {
			m_pRegistry->emplace_or_replace<Selected>(entity);
			m_pRegistry->emplace_or_replace<Outline>(entity, outline);
			m_pRegistry->remove<BlueprintInit>(entity);
		}
	});
}
