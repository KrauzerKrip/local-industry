#pragma once

#include <entt/entt.hpp>

#include "lc_client/eng_input/i_input.h"
#include "game/control/action_control.h"
#include "lc_client/eng_graphics/i_window.h"
#include "lc_client/eng_graphics/graphics_settings.h"
#include "lc_client/eng_graphics/camera/camera.h"
#include "mouse_raycast_observer.h"
#include "lc_client/eng_physics/physics.h"


class MouseRaycast {
public:
	MouseRaycast(Physics* pPhysics, GraphicsSettings* pSettings, IInput* pInput, Camera* pCamera,
		ActionControl* pActionControl,
	entt::registry* pRegistry);

	template <typename... Components, typename... Exclude>
	RaycastResult doMouseRaycast(entt::exclude_t<Exclude...> exclude = {});

private:
	IInput* m_pInput = nullptr;
	ActionControl* m_pActionControl = nullptr;
	Camera* m_pCamera = nullptr;
	Physics* m_pPhysics = nullptr;

	float m_fov;
	glm::vec2 m_windowSize;
	float m_aspectRatio;

	entt::registry* m_pRegistry = nullptr;
};

template <typename... Components, typename... Exclude>
RaycastResult MouseRaycast::doMouseRaycast(entt::exclude_t<Exclude...> exclude) {
	glm::vec2 position = m_pInput->getMousePosition();
	glm::mat4 projection = glm::perspective(glm::radians(m_fov), m_aspectRatio, 0.1f, 1000.0f);
	glm::vec3 mouseWorld = glm::unProject(glm::vec3(position, 0.0f), m_pCamera->getViewMatrix(), projection,
		glm::vec4(0, 0, m_windowSize.x, m_windowSize.y));
	glm::vec3 rayDir = glm::normalize(mouseWorld - m_pCamera->getPosition());

	RaycastQuery query(mouseWorld, rayDir);
	RaycastResult result = m_pPhysics->raycast<Components...>(query, exclude);
	return result;
}