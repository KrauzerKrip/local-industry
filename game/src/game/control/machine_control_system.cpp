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
	addRotationCallback();
	addRemoveCallback();
}

void MachineControlSystem::input() {
	m_isConnection = false;

    auto connectionRequests = m_pRegistry->view<ConnectionRequest, Transform>();
	for (auto&& [entity, request, transform] : connectionRequests.each()) {

		glm::vec3 attachmentPosition;

		if (request.type == ConnectionType::HEAT) {
			attachmentPosition = m_pRegistry->get<HeatOut>(request.entity).position;
		}

		if (request.type != ConnectionType::NONE) {
			Transform& baseTransform = m_pRegistry->get<Transform>(request.entity);

		    glm::vec3 pos = attachmentPosition;
			glm::quat quat = baseTransform.rotation;
			quat *= glm::angleAxis(glm::radians(180.0f), glm::vec3(0.f, 1.f, 0.f));
			glm::vec4 pos4(pos, 0.0);
			pos4 = glm::toMat4(quat) * pos4;
			pos = glm::vec3(pos4.x, pos4.y, pos4.z);

			transform.position = pos + m_pRegistry->get<Transform>(request.entity).position;
			m_isConnection = true;
		}
	}

	auto selectedBlueprints = m_pRegistry->view<Blueprint, Selected, Transform, RelativeTransform>(entt::exclude<Task>);
	if (selectedBlueprints.begin() != selectedBlueprints.end()) {
		RaycastResult result = m_pMouseRaycast->doMouseRaycast(entt::exclude<Selected>);
		if (result.intersectionPoint.has_value()) {
			for (auto&& [ent, transform,  relativeTransform] : selectedBlueprints.each()) {
			    if (m_pRegistry->any_of<Blueprint, Built>(*result.entityIntersectedWith)) {
					m_pRegistry->emplace_or_replace<ConnectionRequest>(ent, *result.entityIntersectedWith);
				} else {
					transform.position = relativeTransform.transform.position + result.intersectionPoint.value();
					transform.position.x = static_cast<int>(transform.position.x);
					transform.position.y = static_cast<int>(transform.position.y);
					transform.position.z = static_cast<int>(transform.position.z);
				}
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
				removeTask(entity);
			}
			else {
				if (!checkIsOrphanAddition(entity)) {
					addTask(entity);
				}
			}
		}
	}
}

void MachineControlSystem::onMouseMove(entt::entity entity, glm::vec3 position, float distance) {
}

bool MachineControlSystem::isConnectable(entt::entity blueprint, entt::entity entityConnectTo) {
	if (m_pRegistry->all_of<HeatIn>(blueprint) && m_pRegistry->all_of<HeatOut>(entityConnectTo)) {
		if (m_pRegistry->get<HeatOut>(entityConnectTo).entity) {
			return false;
		}
	    return true;
	}
    return false;
}


void MachineControlSystem::addSelectionCallback() {
    m_pActionControl->addActionCallback("kb_select", [this]() {
		auto selected = m_pRegistry->view<MachineSelectable, Selected>();
		Outline outline(glm::vec3(255 / 255., 255 / 255., 255 / 255.), 0.025);
		 
		RaycastResult raycastResult = m_pMouseRaycast->doMouseRaycast<MachineSelectable>();

		if (raycastResult.entityIntersectedWith.has_value()) {
			selectOrUnselect(*raycastResult.entityIntersectedWith);
		} else {
			for (auto&& [entity] : selected.each()) {
			    m_pRegistry->remove<Selected>(entity);
			    m_pRegistry->remove<Outline>(entity);
			}
		}

		auto initBlueprints = m_pRegistry->view<Blueprint, BlueprintInit>();
		for (auto&& [entity] : initBlueprints.each()) {
			for (auto&& [entity] : selected.each()) {
				m_pRegistry->remove<Selected>(entity);
				m_pRegistry->remove<Outline>(entity);
			}
			m_pRegistry->emplace_or_replace<Selected>(entity);
			m_pRegistry->emplace_or_replace<Outline>(entity, outline);
			m_pRegistry->remove<BlueprintInit>(entity);
		}
	});
}

void MachineControlSystem::addRotationCallback() {
	m_pActionControl->addActionCallback("kb_rotate_blueprint", [this]() {
		auto selectedBlueprints = m_pRegistry->view<Blueprint, Selected, Transform>(entt::exclude<Task>);

		for (auto&& [entity, transform] : selectedBlueprints.each()) {
			transform.rotation *= glm::angleAxis(glm::radians(-90.0f), glm::vec3(0.f, 1.f, 0.f));
		}
	});
}

void MachineControlSystem::addRemoveCallback() {
	m_pActionControl->addActionCallback("kb_remove_blueprint", [this]() {
		auto selectedBlueprints = m_pRegistry->view<Blueprint, Selected>(entt::exclude<Task>); //TODO: fix and remove exclude

		for (auto&& [entity] : selectedBlueprints.each()) {
			if (m_pRegistry->all_of<Task>(entity)) {
				removeTask(entity);
			}

			m_pRegistry->destroy(entity);
			auto connectionRequests = m_pRegistry->view<Attachment, ConnectionRequest>();
			for (auto&& [ent, request] : connectionRequests.each()) {
				if (request.entity == entity) {
					m_pRegistry->destroy(ent);   
				}
			}
		}
	});
}

void MachineControlSystem::addTask(entt::entity entity) {
	auto selectedCharacter = m_pRegistry->view<GameCharacter, Selected>();
	for (auto&& [characterEntity, character] : selectedCharacter.each()) {
		m_pRegistry->emplace<CharacterAssignedTo>(entity, characterEntity);
	}
	m_pRegistry->emplace<Task>(entity);
}


void MachineControlSystem::removeTask(entt::entity entity) {
    m_pRegistry->remove<Task>(entity);
    if (m_pRegistry->all_of<CharacterAssignedTo>(entity)) {
        m_pRegistry->remove<CharacterAssignedTo>(entity);
    }

	if (!m_pRegistry->all_of<Attachment>(entity)) {
		auto connectionRequests = m_pRegistry->view<Attachment, ConnectionRequest>();
		for (auto&& [ent, request] : connectionRequests.each()) {
			if (request.entity == entity) {
				removeTask(ent);
			}
		}
	}
}

bool MachineControlSystem::checkIsOrphanAddition(entt::entity entity) {
	if (m_pRegistry->all_of<Attachment, ConnectionRequest>(entity)) {
		ConnectionRequest& connectionRequest = m_pRegistry->get<ConnectionRequest>(entity);
		if (connectionRequest.type != ConnectionType::NONE &&
			!m_pRegistry->any_of<Task, Built>(connectionRequest.entity)) {
			return true;
		}
	}
	return false;
}

void MachineControlSystem::selectOrUnselect(entt::entity entity) {
	auto selected = m_pRegistry->view<MachineSelectable, Selected>();
	Outline outline(glm::vec3(255 / 255., 255 / 255., 255 / 255.), 0.025);
	if (selected.begin() == selected.end()) {
		if (m_pRegistry->all_of<MachineSelectable>(entity)) {
			m_pRegistry->emplace_or_replace<Selected>(entity);
			m_pRegistry->emplace_or_replace<Outline>(entity, outline);
		}

		return;
	}

	for (auto&& [ent] : selected.each()) {
		if (ent == entity) {
			m_pRegistry->remove<Selected>(ent);
			m_pRegistry->remove<Outline>(ent);
		}
		else {
			m_pRegistry->remove<Selected>(ent);
			m_pRegistry->remove<Outline>(ent);
			if (m_pRegistry->all_of<MachineSelectable>(entity) && !m_isConnection) {
				m_pRegistry->emplace_or_replace<Selected>(entity);
				m_pRegistry->emplace_or_replace<Outline>(entity, outline);
			}
		}
	}
}

