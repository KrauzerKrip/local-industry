#include "machine_control_system.h"

#include "game/machine/components.h"
#include "game/control/components.h"
#include "lc_client/eng_scene/entt/components.h"
#include "lc_client/eng_graphics/entt/components.h"

#include <iostream>


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

void MachineControlSystem::update() {}

void MachineControlSystem::onSelect(entt::entity entity, glm::vec3 position, float distance) { 

}

void MachineControlSystem::onMouseMove(entt::entity entity, glm::vec3 position, float distance) {

}

void MachineControlSystem::addSelectionCallback() {
	m_pActionControl->addActionCallback("kb_select", [this]() {
		RaycastResult result = m_pMouseRaycast->doMouseRaycast();

		auto selectedBlueprints = m_pRegistry->view<Blueprint, Selected>();

		Outline outline(glm::vec3(1, 1, 1), 0.05);

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
	});
}
