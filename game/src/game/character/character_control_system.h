#pragma once

#include <entt/entt.hpp>

#include "lc_client/eng_input/i_input.h"
#include "game/control/action_control.h"
#include "lc_client/eng_graphics/i_window.h"
#include "lc_client/eng_graphics/graphics_settings.h"
#include "lc_client/eng_graphics/camera/camera.h"


class CharacterControlSystem {
public:
	CharacterControlSystem(GraphicsSettings* pSettings, IInput* pInput, Camera* pCamera, ActionControl* pActionControl, entt::registry* pSceneRegistry, entt::registry* pMapRegistry);

	void input();

private:
	void onSelect(glm::vec2 position);
	void onUnselect(glm::vec2 position);

	IInput* m_pInput = nullptr;
	ActionControl* m_pActionControl = nullptr;
	Camera* m_pCamera = nullptr;

	float m_fov;
	glm::vec2 m_windowSize;
	float m_aspectRatio;

	entt::registry* m_pSceneRegistry = nullptr;
	entt::registry* m_pMapRegistry = nullptr;
};
