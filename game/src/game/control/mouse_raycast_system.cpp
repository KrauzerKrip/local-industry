#include "mouse_raycast_system.h"

#include <iostream>

#include <glm/ext/matrix_projection.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "lc_client/eng_physics/entt/components.h"
#include "components.h"


MouseRaycastSystem::MouseRaycastSystem(GraphicsSettings* pSettings, IInput* pInput, Camera* pCamera,
	ActionControl* pActionControl, entt::registry* pRegistry)
	: m_lastRaycastResult(RaycastResult(std::nullopt, std::nullopt, std::nullopt))
{
	m_pInput = pInput;
	m_pActionControl = pActionControl;
	m_pRegistry = pRegistry;
	m_pCamera = pCamera;

	m_windowSize = glm::vec2(1920, 1080);
	m_fov = pSettings->getFov();
	m_aspectRatio = 16.0f / 9.0f;

	m_pActionControl->addActionCallback("kb_select", [this]() { onSelect(); });	
}

void MouseRaycastSystem::input() {
	doMouseRaycast(m_pInput->getMousePosition());

	//result will be acquired in the after the update
	auto raycastResults = m_pRegistry->view<MouseRaycast, RaycastResult>();

	for (auto&& [entity, raycastResult] : raycastResults.each()) {
		m_lastRaycastResult = raycastResult;
		if (raycastResult.entityIntersectedWith.has_value()) {
			for (MouseRaycastObserver* pObserver : m_observers) {
				pObserver->onMouseMove(raycastResult.entityIntersectedWith.value(), 
					raycastResult.intersectionPoint.value(), 
						raycastResult.intersectionDistance.value());
			}
		}

		m_pRegistry->destroy(entity);
	}
}

void MouseRaycastSystem::addObserver(MouseRaycastObserver* pObserver) { m_observers.push_back(pObserver); }

void MouseRaycastSystem::removeObserver(MouseRaycastObserver* pObserver) { 
	for (auto i = m_observers.begin(); i != m_observers.end(); ++i) {
		if (*i == pObserver) {
			m_observers.erase(i);
		}
	}
}

void MouseRaycastSystem::doMouseRaycast(glm::vec2 position) {
	glm::mat4 projection = glm::perspective(glm::radians(m_fov), m_aspectRatio, 0.1f, 1000.0f);

	glm::vec3 mouseWorld = glm::unProject(glm::vec3(position, 0.0f), m_pCamera->getViewMatrix(), projection,
		glm::vec4(0, 0, m_windowSize.x, m_windowSize.y));

	glm::vec3 rayDir = glm::normalize(mouseWorld - m_pCamera->getPosition());

	RaycastQuery raycastQuery(mouseWorld, rayDir);

	entt::entity entity = m_pRegistry->create();

	m_pRegistry->emplace<RaycastQuery>(entity, raycastQuery);
	m_pRegistry->emplace<MouseRaycast>(entity, MouseRaycast());
}

void MouseRaycastSystem::onSelect() {
	if (m_lastRaycastResult.entityIntersectedWith.has_value()) {
		for (MouseRaycastObserver* pObserver : m_observers) {
			pObserver->onSelect(m_lastRaycastResult.entityIntersectedWith.value(),
				m_lastRaycastResult.intersectionPoint.value(), m_lastRaycastResult.intersectionDistance.value());
		}
	}
}
