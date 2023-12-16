#pragma once

#include <entt/entt.hpp>

#include "lc_client/eng_input/i_input.h"
#include "game/control/action_control.h"
#include "lc_client/eng_graphics/i_window.h"
#include "lc_client/eng_graphics/graphics_settings.h"
#include "lc_client/eng_graphics/camera/camera.h"
#include "mouse_raycast_observer.h"


class MouseRaycastSystem {
public: 
	MouseRaycastSystem(GraphicsSettings* pSettings, IInput* pInput, Camera* pCamera, ActionControl* pActionControl,
		entt::registry* pRegistry);

	void input();
	void addObserver(MouseRaycastObserver* pObserver);
	void removeObserver(MouseRaycastObserver* pObserver);

private:
	void doMouseRaycast(glm::vec2 position);
	void onSelect();


	std::vector<MouseRaycastObserver*> m_observers;
	RaycastResult m_lastRaycastResult;

	IInput* m_pInput = nullptr;
	ActionControl* m_pActionControl = nullptr;
	Camera* m_pCamera = nullptr;

	float m_fov;
	glm::vec2 m_windowSize;
	float m_aspectRatio;

	entt::registry* m_pRegistry = nullptr;
};
