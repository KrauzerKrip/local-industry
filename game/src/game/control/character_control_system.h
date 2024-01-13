#pragma once

#include <entt/entt.hpp>

#include "lc_client/eng_input/i_input.h"
#include "game/control/action_control.h"
#include "lc_client/eng_graphics/i_window.h"
#include "lc_client/eng_graphics/graphics_settings.h"
#include "lc_client/eng_graphics/camera/camera.h"
#include "game/control/mouse_raycast_observer.h"


class CharacterControlSystem : public MouseRaycastObserver {
public:
	CharacterControlSystem(entt::registry* pRegistry);

	void input();
	void update();
	void onAction(std::string action, entt::entity entity, glm::vec3 position, float distance) override;
	void onMouseMove(entt::entity entity, glm::vec3 position, float distance);

private:

	entt::registry* m_pRegistry = nullptr;
};
