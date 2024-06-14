#include "machine_control_system.h"

#include <iostream>

#include <imgui.h>

#include "game/control/components.h"
#include "game/machine/components.h"
#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_scene/entt/components.h"
#include "game/character/components.h"


#include "game/character/task_queue.h"

MachineControlSystem::MachineControlSystem(
	MouseRaycast* pMouseRaycast, ActionControl* pActionControl, entt::registry* pRegistry)
	: m_machineConnector(pRegistry) {
	m_pMouseRaycast = pMouseRaycast;
	m_pActionControl = pActionControl;
	m_pRegistry = pRegistry;

	addSelectionCallback();
	addRotationCallback();
	addRemoveCallback();
}

void MachineControlSystem::input() {
	m_isConnection = false;

    auto connectionRequests = m_pRegistry->view<ConnectionRequest, Transform, RelativeTransform>();
	for (auto&& [entity, request, transform, relativeTransform] : connectionRequests.each()) {

		glm::vec3 attachmentPosition;
		glm::vec3 attachmentRotation;

		auto outputs = m_pRegistry->get<Connections>(request.entity).outputs;

		if (outputs.empty()) {
			continue;
		}

		attachmentPosition = outputs.at(request.resourceType).position;
		attachmentRotation = outputs.at(request.resourceType).rotation;

		if (request.resourceType != ConnectionResourceType::NONE) {
			Transform& baseTransform = m_pRegistry->get<Transform>(request.entity);

		    glm::vec3 pos = attachmentPosition;
			glm::quat quat = baseTransform.rotation;
			quat *= glm::angleAxis(glm::radians(180.0f), glm::vec3(0.f, 1.f, 0.f));
			glm::vec4 pos4(pos, 0.0);
			pos4 = glm::toMat4(quat) * pos4;
			pos = glm::vec3(pos4.x, pos4.y, pos4.z);

			transform.position = pos + m_pRegistry->get<Transform>(request.entity).position + relativeTransform.transform.position;
			transform.rotation = glm::quat(attachmentRotation) * m_pRegistry->get<Transform>(request.entity).rotation * relativeTransform.transform.rotation;
			m_isConnection = true;
		}

		//m_pRegistry->remove<ConnectionRequest>(entity); TODO: make it better
	}

	auto selectedBlueprints = m_pRegistry->view<Blueprint, Selected, Transform, RelativeTransform>(entt::exclude<Task>);
	if (selectedBlueprints.begin() != selectedBlueprints.end()) {
		RaycastResult result = m_pMouseRaycast->doMouseRaycast(entt::exclude<Selected>);
		if (result.intersectionPoint.has_value()) {
			for (auto&& [ent, transform,  relativeTransform] : selectedBlueprints.each()) {
			    if (m_pRegistry->all_of<Connectable>(*result.entityIntersectedWith)) {
					ConnectionRequest& request = m_pRegistry->emplace_or_replace<ConnectionRequest>(ent, ConnectionRequest(*result.entityIntersectedWith));
					auto [resourceType, type] = m_machineConnector.chooseConnection(ent, request.entity);
					request.resourceType = resourceType;
					request.type = type;
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
	Connections& blueprintConnections = m_pRegistry->get<Connections>(blueprint);
	Connections& entityConnections = m_pRegistry->get<Connections>(entityConnectTo);

	for (auto& [resourceType, connection] : blueprintConnections.inputs) {
		for (auto& [resourceType_, connection_] : entityConnections.outputs) {
			if (resourceType == resourceType_) {
				return true;
			}
		}
	}

	for (auto& [resourceType, connection] : blueprintConnections.outputs) {
		for (auto& [resourceType_, connection_] : entityConnections.inputs) {
			if (resourceType == resourceType_) {
				return true;
			}
		}
	}

    return false;
}


void MachineControlSystem::addSelectionCallback() {
    m_pActionControl->addActionCallback("kb_select", [this]() {
		if (ImGui::GetIO().WantCaptureMouse) { // TODO Temporal
			return;
		}

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
	m_pRegistry->emplace<TaskRequest>(entity, TaskRequest("Build"));
	m_pRegistry->emplace_or_replace<Outline>(entity, Outline(glm::vec3(1, 1, 1), 0.025));
}


void MachineControlSystem::removeTask(entt::entity entity) {
	m_pRegistry->emplace<RemoveTaskRequest>(entity, RemoveTaskRequest());

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
	if (m_pRegistry->all_of<Attachment>(entity)) {
		if (m_pRegistry->all_of<ConnectionRequest>(entity)) {
			ConnectionRequest& connectionRequest = m_pRegistry->get<ConnectionRequest>(entity);
			if (connectionRequest.resourceType != ConnectionResourceType::NONE &&
				!m_pRegistry->any_of<Task, Built>(connectionRequest.entity)) {
				return true;
			}
		}
		else {
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

